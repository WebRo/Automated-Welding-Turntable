/*
================================================================================
                    نظام تحكم بطبق لحام آلي - Arduino Mega Sketch
                    Automated Welding Turntable Control System
================================================================================

المشروع: نظام تحكم بطبق لحام آلي متكامل مع Node-RED و الروبوت التعاوني (COBOT)
الإصدار: 5.0 (النسخة النهائية مع وضع التكوين اليدوي والتعليقات المفصلة)
اللوحة: Arduino Mega 2560
تاريخ التحديث: 25 أبريل 2026

الميزات الجديدة بناءً على الطلب الأخير:
- عدم حذف أي نقاط محفوظة عند عمل Homing أو إيقاف الطوارئ.
- زر HOLD أثناء البرنامج يوقف العمل ويطلب Homing جديد.
- أزرار التحكم اليدوية: التحرك للأمام/للخلف، التوقف، الإضافة للقائمة.
================================================================================
*/

// ============================================================================
// دليل توصيل مشغل المحرك (TB6600 Microstep Driver)
// ============================================================================
/*
 المشغل المرفق في صورتك يحتاج لتوصيل من نوع (السالب المشترك - Common Cathode)
 مع لوحة الأردوينو (Arduino Mega) ليعمل بشكل متوافق 100% مع هذا الكود:

 [1] قسم إشارات التحكم (Signal Interface - يُربط بالأردوينو):
 -----------------------------------------------------------------
 • (PUL-) و (DIR-) و (ENA-) : اربط هذه المداخل الثلاثة معاً (بكوبري صغير)، ثم
 صلها بمنفذ الأرضي (GND) في الأردوينو. • (PUL+) [نبضة الخطوة]   : يُوصل بالمنفذ
 رقم (5) في الأردوينو. • (DIR+) [تحديد الاتجاه] : يُوصل بالمنفذ رقم (6) في
 الأردوينو. • (ENA+) [تفعيل المحرك]  : يُوصل بالمنفذ رقم (7) في الأردوينو.
   *ملاحظة برمجية: إرسال (LOW) لمنفذ الـ ENA يُشغل المحرك، وإرسال (HIGH) يفصل
 طاقته لإراحته.

 [2] قسم أسلاك المحرك الخطوي (Motor Interface):
 -----------------------------------------------------------------
 • (A+) و (A-) : يُوصلان بالسلكين الخاصين بالملف الأول للمحرك (Phase A).
 • (B+) و (B-) : يُوصلان بالسلكين الخاصين بالملف الثاني للمحرك (Phase B).
   *لمعرفة الأسلاك المزدوجة، يمكنك استخدام مقياس المقاومة (Avometer) أو تلامس
 الأسلاك.

 [3] قسم الطاقة الرئيسية (Power Interface):
 -----------------------------------------------------------------
 • (VCC) : يُوصل بالموجب (+) لمصدر طاقة خارجي (محول 12 فولت أو 24 فولت DC).
 • (GND) : يُوصل بالسالب (-) لنفس مصدر الطاقة الخارجي.

 ⚠️ تحذير أمان هام جداً: لا تقم أبداً بفصل أو تركيب أسلاك المحرك (A و B) بينما تكون
 طاقة الـ 12V/24V موصلة بالدرايفر، لأن ذلك سيتلف الدرايفر فوراً!
*/

// ============================================================================
// [1] استدعاء المكتبات الأساسية (Libraries)
// ============================================================================
#include <AccelStepper.h> // مكتبة للتحكم الدقيق بحركة المحرك الخطوي (التسارع والسرعة)
#include <Adafruit_NeoPixel.h> // مكتبة للتحكم في الإضاءة الذكية (لمبة LED واحدة)
#include <Arduino.h> // مكتبة الأردوينو الأساسية (مهمة لكل المشاريع)

// ============================================================================
// [2] تعريفات أطراف التوصيل للأجهزة (Hardware Pins)
// ============================================================================

// أطراف المحرك الخطوي (Stepper Motor Pins)
const int STEP_PIN = 5; // المخرج المسؤول عن إرسال النبضات للمحرك للتحرك
const int DIR_PIN = 6; // المخرج المسؤول عن تحديد اتجاه دوران المحرك
const int ENABLE_PIN = 7; // المخرج المسؤول عن تفعيل/إيقاف المحرك (LOW = تشغيل)

// أطراف مستشعرات الموضع (Sensor)
const int SENSOR_PIN = 8; // مدخل مستشعر العودة للصفر (Homing Sensor)
#define SENSOR_HOME_STATE                                                      \
  LOW // تم التعديل إلى LOW لاستخدام المقاومة الداخلية لمنع التشويش

// أطراف التواصل مع الروبوت التعاوني (Cobot Relays)
const int RELAY_TO_COBOT =
    9;
const int RELAY_TO_COBOT_OFF = HIGH;
const int RELAY_TO_COBOT_ON = LOW; // تفعيل ريلاي الروبوت يكون بإخراج LOW لأن الريلاي يعمل بنظام Active-Low
const int RELAY_FROM_COBOT =
    10; // مدخل لاستقبال إشارة من الروبوت تفيد بأنه انتهى من اللحام

// أطراف إضاءة الحالة (Status LED)
const int LED_PIN = 11; // مخرج إرسال البيانات للمبة LED WS2812
const int LED_COUNT =
    1; // عدد اللمبات المستخدمة في الشريط (نستخدم لمبة واحدة فقط)

// ============================================================================
// [3] إعدادات الحركة والتوقيت (Timing & Motor Specifications)
// ============================================================================

// إعدادات سرعات المحرك
#define MAX_SPEED 1000.0 // أقصى سرعة يصل لها المحرك (بالنبضات في الثانية)
#define ACCELERATION                                                           \
  500.0 // مقدار تسارع وتباطؤ المحرك (لتجنب الاهتزاز والقفزات)
#define HOMING_SPEED                                                           \
  300.0 // سرعة المحرك أثناء عملية البحث عن نقطة الصفر (نجعلها بطيئة للأمان)
#define MANUAL_SPEED                                                           \
  500.0 // مقدار تسارع وتباطؤ المحرك (لتجنب الاهتزاز والقفزات)

// إعدادات الدرجات والنسب
#define STEPS_PER_REVOLUTION                                                   \
  200 // عدد النبضات اللازمة لعمل دورة كاملة للمحرك (قياسي)

// إعدادات التوقيتات الدقيقة (بالملي ثانية)
#define RELAY_PULSE_MS                                                         \
  1000 // مدة النبضة التي ترسل للروبوت للبدء (يجب أن تكون 1 ثانية بالضبط)
#define COBOT_TIMEOUT_MS                                                       \
  120000 // مهلة الانتظار للروبوت (دقيقتين، إذا تأخر يعتبر خطأ)
#define HOMING_TIMEOUT_MS                                                      \
  30000 // مهلة عملية التصفير (30 ثانية لتجنب دوران المحرك للأبد إذا كان
        // المستشعر تالفاً)
#define STATUS_UPDATE_INTERVAL_MS                                              \
  100 // معدل إرسال تحديث الزاوية لـ Node-RED (كل 100 ملي ثانية)
#define COUNTDOWN_UPDATE_INTERVAL_MS                                           \
  1000 // مدة النبضة التي ترسل للروبوت للبدء (يجب أن تكون 1 ثانية بالضبط)
#define PROGRAM_ACCELERATION                                                   \
  3000.0 // تسارع معقول لضمان الدقة ومنع فقدان الخطوات أثناء البرنامج
#define START_DELAY_MS \
  2000 // تأخير 2 ثانية بعد استلام إشارة الروبوت قبل بدء حركة الطاولة

// ============================================================================
// [4] ألوان الإضاءة (LED Status Colors)
// ============================================================================

const uint32_t LED_GREEN = Adafruit_NeoPixel::Color(
    0, 255, 0); // أخضر: النظام جاهز للعمل، أو انتهت المهمة بنجاح
const uint32_t LED_BLUE = Adafruit_NeoPixel::Color(
    0, 0, 255); // أزرق: المحرك يتحرك الآن (تصفير أو حركة لزاوية)
const uint32_t LED_YELLOW = Adafruit_NeoPixel::Color(
    255, 255, 0); // أصفر: إما الروبوت يلحم، أو أن الزاوية تم حفظها يدوياً
const uint32_t LED_RED = Adafruit_NeoPixel::Color(
    255, 0, 0); // أحمر: خطأ، أو تم ضغط زر الطوارئ ويطلب تصفير جديد

// ============================================================================
// [5] حالات النظام (System States Machine)
// ============================================================================

enum SystemState {
  IDLE, // حالة الجاهزية (النظام متوقف وينتظر أوامر)
  HOMING, // حالة التصفير (المحرك يبحث عن المستشعر)
  MANUAL_MOVING, // حالة الدوران اليدوي المستمر (عند ضغط Move F/B)
  MANUAL_DECELERATING, // حالة التباطؤ (عند ضغط HOLD ليتوقف المحرك بنعومة)
  MANUAL_HOLD, // حالة التوقف التام (متوقف وجاهز ليتم حفظ الزاوية بزر ADD)
  ARMED, // *** جديد *** النظام مُسلَّح وينتظر إشارة الروبوت (Pin 10) لبدء/إعادة الدورة
  DELAY_BEFORE_START, // *** جديد *** انتظار 2 ثانية بعد استلام إشارة الروبوت قبل تحريك الطاولة
  PROGRAM_MOVING, // حالة تنفيذ البرنامج (يتحرك للزاوية التالية في القائمة)
  RELAY_ACTIVE, // حالة تفعيل الريلاي (إرسال إشارة 1 ثانية للروبوت)
  WAITING_COBOT, // حالة انتظار الروبوت (ينتظر رد الروبوت بأنه انتهى)
  DELAY_BEFORE_MOVE, // حالة الانتظار 3 ثواني لتفادي اصطدام الروبوت
  WELD_COMPLETE_DELAY, // تأخير مجهري 50 ملي ثانية لتحديث اللمبة بدون تجميد
  RETURNING_HOME, // حالة العودة لنقطة الصفر في نهاية البرنامج (بدون تجميد)
  MANUAL_GO_HOME,
  ERROR, // حالة الخطأ أو الطوارئ (لا يمكن عمل شيء إلا بعد التصفير من جديد)
  PROGRAM_COMPLETE,   // حالة اكتمال البرنامج (غير مستخدمة في الوضع الحالي)
  PROGRAM_PAUSED,
  MANUAL_GO_TO_POS
};

// ============================================================================
// [6] المتغيرات العامة (Global Variables)
// ============================================================================

SystemState currentState =
    IDLE; // المتغير الذي يحفظ حالة النظام الحالية (يبدأ جاهزاً)
bool isHomed =
    false; // هل تم تصفير النظام؟ (يمنع أي حركة إذا كانت القيمة False)
bool programRunning = false; // هل يوجد برنامج لحام يعمل الآن؟
bool programPaused = false;
SystemState pausedState = IDLE;
long pausedTargetPosition = 0;
unsigned long pausedDelayRemainingMs = 0;
unsigned long pausedCobotRemainingMs = 0;
unsigned long pausedCountdownRemainingMs = 0;
bool pausedCobotFinishedSignal = false;
float speedPercentage = 100.0;
unsigned long cobotTimeoutMs = COBOT_TIMEOUT_MS;

// متغيرات مصفوفة النقاط والزوايا
int totalPositions = 0; // إجمالي عدد الزوايا المحفوظة في القائمة
int currentPositionIndex = 0; // الفهرس الذي يشير للنقطة الجاري تنفيذها حالياً
long targetStepsArray[30]; // مصفوفة يمكنها تخزين حتى 30 زاوية مختلفة كحد أقصى

// متغيرات التوقيت وحفظ الوقت
unsigned long relayStartTime =
    0; // وقت بدء تشغيل ريلاي الروبوت (لحساب الـ 1 ثانية)
unsigned long cobotWaitStartTime =
    0; // وقت بدء تشغيل ريلاي الروبوت (لحساب الـ 1 ثانية)
unsigned long homingStartTime = 0; // وقت بدء التصفير (لحساب مهلة الـ 30 ثانية)
unsigned long lastStatusTime = 0; // وقت آخر إرسال للزاوية (لحساب كل 100ms)
unsigned long lastCountdownTime =
    0; // وقت بدء تشغيل ريلاي الروبوت (لحساب الـ 1 ثانية)
unsigned long delayStartTime = 0; // وقت بدء انتظار الـ 3 ثواني للروبوت

// إنشاء الكائنات من المكتبات (Objects Initialization)
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN,
                        NEO_GRB + NEO_KHZ800); // إنشاء كائن الإضاءة
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN,
                     DIR_PIN); // إنشاء كائن المحرك

// الإعلان المسبق عن جميع الدوال قبل استخدامها (Function Prototypes)
void processCommand(String cmd);
void performHoming();
void handleMoveForward();
void handleMoveBackward();
void handleHold();
void handleAdd();
void handleGoHome();
void handleGoToPos(String cmd);
void handleSetHomeHere();
void handleDisarm(); // *** جديد *** إلغاء التسليح عند تدخل المشغّل
void handleProgramPause();
void handleStopKeepHome();
void handleEmergencyStop();
void startProgram(String cmd);
void moveToCurrentTarget();
void handleSystemState();
void activateRelayToCobot();
void completeWeldPosition();
void handleError(String errorMsg);
void updateLED(uint32_t color);
void sendToNodeRED(String message);

// ============================================================================
// [7] دالة الإعداد الأساسية - setup() - وتنفذ مرة واحدة عند الإقلاع
// ============================================================================

void setup() {
  // 1. فتح المنفذ التسلسلي للتواصل مع Node-RED
  Serial.begin(9600);
  Serial.setTimeout(50); // تسريع وقت استجابة السيريال

  // 2. إعداد اتجاهات دبابيس الأردوينو
  pinMode(STEP_PIN, OUTPUT); // مخرج نبضات المحرك
  pinMode(DIR_PIN, OUTPUT); // مخرج اتجاه دوران المحرك
  pinMode(ENABLE_PIN, OUTPUT); // مخرج تفعيل المحرك
  pinMode(RELAY_TO_COBOT, OUTPUT); // مخرج ريلاي الروبوت (إرسال الإشارة)

  pinMode(SENSOR_PIN,
          INPUT_PULLUP); // مدخل مستشعر الصفر (مقاومة رفع داخلية مفعلة)
  pinMode(RELAY_FROM_COBOT,
          INPUT_PULLUP); // مدخل مستشعر الصفر (مقاومة رفع داخلية مفعلة)

  // 3. ضبط القيم الأولية للأمان
  digitalWrite(ENABLE_PIN,
               HIGH); // تعطيل المحرك في البداية (HIGH يعطل المحرك في الغالب)
  digitalWrite(RELAY_TO_COBOT, RELAY_TO_COBOT_OFF); // إبقاء ريلاي إشارة الروبوت مفصولاً عند بدء التشغيل

  // 4. إعدادات مكتبة المحرك (السرعة القصوى والتسارع)
  stepper.setMaxSpeed(MAX_SPEED * (speedPercentage / 100.0));
  stepper.setAcceleration(ACCELERATION);

  // 5. تشغيل إضاءة الـ LED ووضعها على اللون الأخضر دلالة على الجاهزية
  strip.begin();
  strip.setBrightness(255); // أقصى سطوع
  updateLED(LED_GREEN);

  // 6. إرسال إشعار لـ Node-RED بأن النظام اشتغل
  sendToNodeRED("SYSTEM_READY");
}

// ============================================================================
// [8] دالة الدوران الأساسية - loop() - وتتكرر للأبد وبسرعة قصوى
// ============================================================================

void loop() {
  // 1. قراءة واستقبال أي أمر جديد من Node-RED عبر السيريال
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); // القراءة حتى نهاية السطر
    command.trim(); // تنظيف المسافات الزائدة
    if (command.length() > 0) {
      processCommand(command); // تمرير الأمر لدالة معالجة الأوامر
    }
  }

  // 2. تحديث المحرك باستمرار (Non-blocking) - لضمان نعومة الحركة وعدم توقف
  // المعالج
  if (programPaused && pausedState == WAITING_COBOT &&
      !pausedCobotFinishedSignal && digitalRead(RELAY_FROM_COBOT) == LOW) {
    pausedCobotFinishedSignal = true;
    sendToNodeRED("STATUS:COBOT_FINISHED_SIGNAL_STORED_DURING_PAUSE");
  }
  if (currentState == MANUAL_MOVING) {
    stepper.runSpeed(); // الدوران اليدوي يعتمد على سرعة ثابتة ومستمرة
  }
  // للحركة الموجهة (التصفير، تباطؤ، أو الذهاب لهدف محدد): نستخدم run()
  else if (stepper.distanceToGo() != 0 || currentState == MANUAL_DECELERATING ||
           currentState == PROGRAM_MOVING || currentState == RETURNING_HOME ||
           currentState == HOMING || currentState == MANUAL_GO_HOME ||
           currentState == MANUAL_GO_TO_POS) {
    stepper.run();
  }

  // 3. تشغيل دالة إدارة حالة النظام (لمتابعة مراحل اللحام أو التباطؤ)
  handleSystemState();
}

// ============================================================================
// [9] دالة معالجة الأوامر وتحويلها (Command Processing)
// ============================================================================

void processCommand(String cmd) {
  // توزيع المهام حسب الأمر الوارد من Node-RED
  if (cmd == "HOMING") {
    performHoming(); // بدء عملية التصفير والعودة للصفر
  } else if (cmd == "MOVE_FORWARD") {
    handleMoveForward(); // دوران يدوي للأمام
  } else if (cmd == "MOVE_BACKWARD") {
    handleMoveBackward(); // دوران يدوي للخلف
  } else if (cmd == "HOLD") {
    handleHold(); // التوقف أثناء الحركة (يدوياً لالتقاط نقطة، أو برمجياً للطوارئ)
  } else if (cmd == "ADD") {
    handleAdd(); // إضافة الزاوية الحالية للمصفوفة
  } else if (cmd == "GO_HOME") {
    handleGoHome();
  } else if (cmd.startsWith("GO_TO_POS ")) {
    handleGoToPos(cmd);
  } else if (cmd == "SET_HOME_HERE") {
    handleSetHomeHere();
  } else if (cmd == "DISARM") {
    handleDisarm(); // *** جديد *** المشغّل تدخّل أثناء ARMED → إلغاء التسليح والعودة لـ IDLE
  } else if (cmd == "PAUSE_PROGRAM") {
    handleProgramPause();
  } else if (cmd == "STOP") {
    handleStopKeepHome();
  } else if (cmd == "ESTOP") {
    handleEmergencyStop();
  } else if (cmd.startsWith("START_PROGRAM")) {
    startProgram(cmd); // بدء تنفيذ اللحام عبر النقاط
  } else if (cmd.startsWith("SET_COBOT_TIMEOUT ")) {
    long timeoutSeconds = cmd.substring(18).toInt();
    if (timeoutSeconds >= 0 && timeoutSeconds <= 3600) {
      cobotTimeoutMs = (unsigned long)timeoutSeconds * 1000UL;
      sendToNodeRED(cobotTimeoutMs == 0 ? "STATUS:COBOT_TIMEOUT_DISABLED" : "STATUS:COBOT_TIMEOUT_SET");
    } else {
      sendToNodeRED("ERROR:INVALID_COBOT_TIMEOUT");
    }
  } else if (cmd.startsWith("SET_SPEED ")) {
    float newSpeed = cmd.substring(10).toFloat();
    if (newSpeed >= 1.0 && newSpeed <= 100.0) {
      speedPercentage = newSpeed;
      if (currentState != HOMING) stepper.setMaxSpeed(MAX_SPEED * (speedPercentage / 100.0));
      sendToNodeRED("STATUS:SPEED_SET_TO_" + String((int)speedPercentage));
    }
  } else if (cmd == "STATUS") {
    // إذا طلب Node-RED حالة النظام نرسل له حزمة معلومات (الزاوية، الحالة، هل تم
    // التصفير)
    long steps = stepper.currentPosition();
    sendToNodeRED("STATUS|HOMED:" + String(isHomed ? "1" : "0") +
                  "|PROG:" + String(programRunning ? "1" : "0") +
                  "|PAUSED:" + String(programPaused ? "1" : "0") +
                  "|POS:" + String(steps) + "|STATE:" + String(currentState));
  } else {
    // رسالة للأوامر غير المعروفة
    sendToNodeRED("ERROR:INVALID_COMMAND:" + cmd);
  }
}

// ============================================================================
// [10] أزرار وإجراءات التكوين اليدوي (Manual Configuration Buttons)
// ============================================================================

// دالة التصفير والبحث عن نقطة الصفر (Homing)
void performHoming() {
  // لا يمكن التصفير إذا كان البرنامج قيد التنفيذ لحماية النظام
  if (programRunning) {
    sendToNodeRED("ERROR:CANNOT_HOME_DURING_PROGRAM");
    return;
  }

  sendToNodeRED("STATUS:HOMING_STARTED");
  updateLED(LED_BLUE); // تغيير الإضاءة للون الأزرق لتدل على الحركة

  digitalWrite(ENABLE_PIN, LOW); // تشغيل وتمكين المحرك
  stepper.setMaxSpeed(HOMING_SPEED); // استخدام السرعة البطيئة المخصصة للتصفير
  stepper.setAcceleration(ACCELERATION); // استخدام التسارع لمنع توقف الموتور المفاجئ (Stall)
  stepper.move(1000000); // إعطاء هدف بعيد جداً للأمام ليستمر بالدوران حتى يلمس المستشعر

  homingStartTime = millis(); // حفظ وقت البداية لعد 30 ثانية للطوارئ
  currentState = HOMING;

  // سيتم استكمال التصفير في handleSystemState() بدون أي loop يعطل المعالج
}

// دالة التحرك اليدوي للأمام باستمرار
void handleMoveForward() {
  if (!isHomed) {
    sendToNodeRED("ERROR:MOVE_BEFORE_HOMING");
    return;
  } // رفض التحرك قبل التصفير
  if (programRunning && !programPaused) {
    sendToNodeRED("ERROR:MOVE_DURING_PROGRAM");
    return;
  } // رفض التحرك قبل التصفير

  digitalWrite(ENABLE_PIN, LOW); // تشغيل وتمكين المحرك
  stepper.setMaxSpeed(MAX_SPEED * (speedPercentage / 100.0));
  stepper.setSpeed(MANUAL_SPEED * (speedPercentage / 100.0)); // إعطاء سرعة موجبة للدوران اليدوي باتجاه CW

  currentState = MANUAL_MOVING; // تغيير الحالة لدوران يدوي
  updateLED(LED_BLUE); // تغيير الإضاءة للون الأزرق لتدل على الحركة

  sendToNodeRED("STATUS:MOVING_FORWARD_CONTINUOUS");
  sendToNodeRED("STATUS:PRESS_HOLD_TO_CAPTURE_POSITION");
}

// دالة التحرك اليدوي للخلف باستمرار
void handleMoveBackward() {
  if (!isHomed) {
    sendToNodeRED("ERROR:MOVE_BEFORE_HOMING");
    return;
  }
  if (programRunning && !programPaused) {
    sendToNodeRED("ERROR:MOVE_DURING_PROGRAM");
    return;
  }

  digitalWrite(ENABLE_PIN, LOW); // تشغيل وتمكين المحرك
  stepper.setMaxSpeed(MAX_SPEED * (speedPercentage / 100.0));
  stepper.setSpeed(-MANUAL_SPEED * (speedPercentage / 100.0)); // إعطاء سرعة سالبة للدوران اليدوي باتجاه CCW

  currentState = MANUAL_MOVING;
  updateLED(LED_BLUE);

  sendToNodeRED("STATUS:MOVING_BACKWARD_CONTINUOUS");
  sendToNodeRED("STATUS:PRESS_HOLD_TO_CAPTURE_POSITION");
}

// دالة الإيقاف (HOLD)
void handleHold() {
  if (!isHomed) {
    sendToNodeRED("ERROR:HOLD_BEFORE_HOMING");
    return;
  }

  // إذا تم ضغط زر HOLD أثناء تنفيذ برنامج اللحام، فإنه يعمل كموقف طوارئ
  // للبرنامج (حسب طلبك: يوقف البرنامج ويطلب تصفير جديد، ولكن دون حذف النقاط
  // المحفوظة)
  if (programRunning && !programPaused) {
    stepper.stop(); // توقيف المحرك بنعومة
    digitalWrite(RELAY_TO_COBOT, RELAY_TO_COBOT_OFF); // إيقاف ريلاي اللحام عند إيقاف الحركة اليدوية
    programRunning = false; // إيقاف عمل البرنامج
    isHomed = false; // إبطال التصفير لاجبار المستخدم على التصفير مجدداً
    currentState = ERROR; // تحويل حالة النظام لخطأ
    updateLED(LED_RED); // اللمبة حمراء
    sendToNodeRED("STATUS:PROGRAM_STOPPED_BY_HOLD");
    sendToNodeRED("STATUS:SYSTEM_REQUIRES_NEW_HOMING");
    return;
  }

  // إذا كان النظام في وضع التحرك اليدوي (أردنا التقاط النقطة)
  if (currentState != MANUAL_MOVING) {
    return; // إذا لم يكن هناك حركة، فلا داعي لعمل شيء
  }

  stepper.setSpeed(0); // توقف مفاجئ
  currentState = MANUAL_HOLD; // تغيير الحالة للتوقف التام
  long currentSteps = stepper.currentPosition();
  updateLED(LED_YELLOW); // الإضاءة صفراء لتأكيد توقف المحرك وجاهزيته للحفظ
  sendToNodeRED("STATUS:MOTOR_STOPPED");
  sendToNodeRED("STATUS:POSITION_CAPTURED_AT_" + String(currentSteps) +
                "_STEPS");
  sendToNodeRED(
      "STATUS:ADD_BUTTON_NOW_ENABLED"); // إبلاغ المستخدم بضغط زر ADD للحفظ

  // يتم متابعة إكمال التوقف في دالة handleSystemState()
}

// دالة إضافة الزاوية الحالية للقائمة (ADD)
void handleAdd() {
  if (!isHomed) {
    sendToNodeRED("ERROR:ADD_BEFORE_HOMING");
    return;
  } // رفض التحرك قبل التصفير
  if (programRunning) {
    sendToNodeRED("ERROR:ADD_DURING_PROGRAM");
    return;
  } // رفض التحرك قبل التصفير
  // الزر ADD يعمل فقط إذا كنت قد ضغطت HOLD قبله (والمحرك في وضع التوقف لالتقاط
  // الزاوية)
  if (currentState != MANUAL_HOLD) {
    sendToNodeRED("ERROR:ADD_REQUIRES_HOLD_FIRST");
    return;
  }

  // منع زيادة الزوايا عن الحد الأقصى للمصفوفة (30)
  if (totalPositions >= 30) {
    sendToNodeRED("ERROR:MAX_POSITIONS_REACHED");
    return;
  }

  // قراءة الزاوية الحالية للمحرك بدقة
  long currentSteps = stepper.currentPosition();
  // تخزين الزاوية في المصفوفة الداخلية للأردوينو
  targetStepsArray[totalPositions] = currentSteps;
  totalPositions++; // زيادة عداد النقاط بمقدار 1

  // إرسال تأكيدات للـ Node-RED ليعرضها في الداشبورد
  sendToNodeRED("STATUS:POSITION_SAVED");
  sendToNodeRED("STATUS:POS_" + String(totalPositions) + "_AT_" +
                String(currentSteps) + "_STEPS_ADDED");
  sendToNodeRED("STATUS:READY_FOR_NEXT_POSITION");

  updateLED(LED_GREEN); // الإضاءة خضراء لتأكيد الحفظ بنجاح
  currentState = IDLE; // إعادة النظام لحالة الجاهزية لاستقبال الحركة التالية
}

void handleGoHome() {
  if (!isHomed) {
    sendToNodeRED("ERROR:MUST_BE_HOMED_FIRST");
    return;
  }
  if ((programRunning && !programPaused) || currentState == ARMED) {
    sendToNodeRED("ERROR:CANNOT_MOVE_DURING_PROGRAM");
    return;
  }

  digitalWrite(ENABLE_PIN, LOW);
  updateLED(LED_BLUE);
  stepper.setMaxSpeed(MAX_SPEED * (speedPercentage / 100.0));
  stepper.setAcceleration(PROGRAM_ACCELERATION);
  if (stepper.currentPosition() != 0) {
    stepper.moveTo(stepper.currentPosition());
    stepper.moveTo(0);
  }
  currentState = MANUAL_GO_HOME;
  sendToNodeRED("STATUS:MOVING_TO_HOME_POSITION");
}

void handleGoToPos(String cmd) {
  if (!isHomed) {
    sendToNodeRED("ERROR:MUST_BE_HOMED_FIRST");
    return;
  }
  if ((programRunning && !programPaused) || currentState == ARMED) {
    sendToNodeRED("ERROR:CANNOT_MOVE_DURING_PROGRAM");
    return;
  }
  if (currentState == HOMING || currentState == MANUAL_MOVING ||
      currentState == MANUAL_DECELERATING || currentState == MANUAL_GO_HOME ||
      currentState == MANUAL_GO_TO_POS) {
    sendToNodeRED("ERROR:MOTOR_BUSY");
    return;
  }

  long targetSteps = cmd.substring(10).toInt();
  if (targetSteps < 0) {
    sendToNodeRED("ERROR:INVALID_TARGET_POSITION");
    return;
  }

  digitalWrite(ENABLE_PIN, LOW);
  updateLED(LED_BLUE);
  stepper.setMaxSpeed(MAX_SPEED * (speedPercentage / 100.0));
  stepper.setAcceleration(PROGRAM_ACCELERATION);
  stepper.moveTo(stepper.currentPosition());
  stepper.moveTo(targetSteps);
  currentState = MANUAL_GO_TO_POS;
  sendToNodeRED("STATUS:MOVING_TO_SELECTED_POSITION");
}

void handleSetHomeHere() {
  if ((programRunning && !programPaused) || currentState == ARMED) {
    sendToNodeRED("ERROR:CANNOT_SET_HOME_DURING_PROGRAM");
    return;
  }

  stepper.setSpeed(0);
  stepper.setCurrentPosition(0);
  isHomed = true;
  currentState = IDLE;
  updateLED(LED_GREEN);
  sendToNodeRED("HOMED");
  sendToNodeRED("STEPS:0");
  sendToNodeRED("STATUS:NEW_HOME_SET_SUCCESSFULLY");
}
// ============================================================================
// *** جديد *** دالة إلغاء التسليح عند تدخّل المشغّل (DISARM)
// تُستدعى عندما يضغط المشغّل أي زر (CW/CCW/HOLD/ADD/DELETE/EDIT...) أثناء ARMED
// ============================================================================
void handleDisarm() {
  // إلغاء التسليح يعمل فقط إذا كان النظام في حالة ARMED
  if (currentState != ARMED) {
    sendToNodeRED("STATUS:NOT_ARMED_IGNORING_DISARM");
    return;
  }

  programRunning = false; // إيقاف عمل البرنامج
  programPaused = false;
  pausedCobotFinishedSignal = false;
  currentState = IDLE; // إعادة النظام لحالة الجاهزية لاستقبال الحركة التالية
  updateLED(LED_GREEN); // الإضاءة خضراء لتأكيد الحفظ بنجاح
  sendToNodeRED("STATUS:DISARMED_BY_OPERATOR");
  sendToNodeRED("STATUS:CONFIGURATION_UNLOCKED"); // الأزرار متاحة مجدداً
  sendToNodeRED("STATUS:PRESS_START_WHEN_READY"); // تذكير بضغط START عند الانتهاء
}

// دالة الإيقاف الكلي والطوارئ (STOP / ESTOP)
void handleProgramPause() {
  if (!programRunning && !programPaused) {
    sendToNodeRED("ERROR:PAUSE_ONLY_AFTER_START");
    return;
  }

  if (programPaused) {
    SystemState resumeState = pausedState;
    stepper.setSpeed(0);
    programPaused = false;
    currentState = resumeState;
    digitalWrite(ENABLE_PIN, LOW);

    if (resumeState == PROGRAM_MOVING || resumeState == RETURNING_HOME) {
      stepper.moveTo(stepper.currentPosition());
      stepper.moveTo(pausedTargetPosition);
    } else if (resumeState == RELAY_ACTIVE) {
      relayStartTime = millis() - (RELAY_PULSE_MS - pausedDelayRemainingMs);
      digitalWrite(RELAY_TO_COBOT, RELAY_TO_COBOT_ON);
    } else if (resumeState == DELAY_BEFORE_START) {
      delayStartTime = millis() - (START_DELAY_MS - pausedDelayRemainingMs);
    } else if (resumeState == DELAY_BEFORE_MOVE) {
      delayStartTime = millis() - (3000UL - pausedDelayRemainingMs);
    } else if (resumeState == WELD_COMPLETE_DELAY) {
      delayStartTime = millis() - (50UL - pausedDelayRemainingMs);
    } else if (resumeState == WAITING_COBOT) {
      if (pausedCobotFinishedSignal) {
        currentState = DELAY_BEFORE_MOVE;
        delayStartTime = millis();
        pausedCobotFinishedSignal = false;
        updateLED(LED_YELLOW);
        sendToNodeRED("STATUS:COBOT_FINISHED_WHILE_PAUSED");
        sendToNodeRED("STATUS:COBOT_FINISHED_WAITING_3_SECONDS");
      } else {
        if (cobotTimeoutMs > 0) cobotWaitStartTime = millis() - (cobotTimeoutMs - pausedCobotRemainingMs);
        lastCountdownTime = millis() - (COUNTDOWN_UPDATE_INTERVAL_MS - pausedCountdownRemainingMs);
      }
    }

    updateLED(resumeState == PROGRAM_MOVING || resumeState == RETURNING_HOME ? LED_BLUE : LED_YELLOW);
    sendToNodeRED("STATUS:PROGRAM_RESUMED");
    return;
  }

  switch (currentState) {
  case ARMED:
  case DELAY_BEFORE_START:
  case PROGRAM_MOVING:
  case RELAY_ACTIVE:
  case WAITING_COBOT:
  case DELAY_BEFORE_MOVE:
  case WELD_COMPLETE_DELAY:
  case RETURNING_HOME:
    pausedState = currentState;
    break;
  default:
    sendToNodeRED("ERROR:CANNOT_PAUSE_NOW");
    return;
  }

  pausedTargetPosition = stepper.targetPosition();
  pausedCobotFinishedSignal = false;
  pausedDelayRemainingMs = 0;
  pausedCobotRemainingMs = 0;
  pausedCountdownRemainingMs = 0;

  if (currentState == PROGRAM_MOVING || currentState == RETURNING_HOME) {
    stepper.moveTo(stepper.currentPosition());
  } else if (currentState == RELAY_ACTIVE) {
    unsigned long elapsed = millis() - relayStartTime;
    pausedDelayRemainingMs = elapsed >= RELAY_PULSE_MS ? 0 : RELAY_PULSE_MS - elapsed;
    digitalWrite(RELAY_TO_COBOT, RELAY_TO_COBOT_OFF);
  } else if (currentState == DELAY_BEFORE_START) {
    unsigned long elapsed = millis() - delayStartTime;
    pausedDelayRemainingMs = elapsed >= START_DELAY_MS ? 0 : START_DELAY_MS - elapsed;
  } else if (currentState == DELAY_BEFORE_MOVE) {
    unsigned long elapsed = millis() - delayStartTime;
    pausedDelayRemainingMs = elapsed >= 3000UL ? 0 : 3000UL - elapsed;
  } else if (currentState == WELD_COMPLETE_DELAY) {
    unsigned long elapsed = millis() - delayStartTime;
    pausedDelayRemainingMs = elapsed >= 50UL ? 0 : 50UL - elapsed;
  } else if (currentState == WAITING_COBOT) {
    if (cobotTimeoutMs > 0) {
      unsigned long elapsed = millis() - cobotWaitStartTime;
      pausedCobotRemainingMs = elapsed >= cobotTimeoutMs ? 0 : cobotTimeoutMs - elapsed;
    }
    unsigned long countdownElapsed = millis() - lastCountdownTime;
    pausedCountdownRemainingMs = countdownElapsed >= COUNTDOWN_UPDATE_INTERVAL_MS ? 0 : COUNTDOWN_UPDATE_INTERVAL_MS - countdownElapsed;
  }

  programPaused = true;
  currentState = PROGRAM_PAUSED;
  updateLED(LED_YELLOW);
  sendToNodeRED("STATUS:PROGRAM_PAUSED");
}
void handleStopKeepHome() {
  if (!programRunning && !programPaused && currentState != ARMED) {
    sendToNodeRED("ERROR:STOP_ONLY_WHILE_PROGRAM_ACTIVE");
    return;
  }

  stepper.stop();
  stepper.setCurrentPosition(stepper.currentPosition());
  digitalWrite(ENABLE_PIN, HIGH);
  digitalWrite(RELAY_TO_COBOT, RELAY_TO_COBOT_OFF);

  programRunning = false;
  programPaused = false;
  pausedCobotFinishedSignal = false;
  pausedDelayRemainingMs = 0;
  pausedCobotRemainingMs = 0;
  pausedCountdownRemainingMs = 0;
  currentPositionIndex = 0;
  currentState = IDLE;

  updateLED(LED_GREEN);
  sendToNodeRED("STATUS:PROGRAM_STOPPED_KEEP_HOME");
  sendToNodeRED("STATUS:PRESS_START_WHEN_READY");
}

void handleEmergencyStop() {
  stepper.stop(); // توقيف المحرك بنعومة
  stepper.setCurrentPosition(
      stepper.currentPosition()); // تثبيت مكانه كهدف لعدم استكمال الحركة
  digitalWrite(ENABLE_PIN, HIGH); // فصل الطاقة كلياً عن المحرك للأمان
  digitalWrite(RELAY_TO_COBOT, RELAY_TO_COBOT_OFF); // فصل إشارة اللحام عن الروبوت فور إيقاف البرنامج

  isHomed = false; // إبطال التصفير لاجبار المستخدم على التصفير مجدداً
  programRunning = false; // إيقاف عمل البرنامج
  programPaused = false;
  pausedCobotFinishedSignal = false;
  currentState = ERROR; // تحويل حالة النظام لخطأ

  // لاحظ: لا يتم حذف النقاط المحفوظة هنا أيضاً، لتبقى معروضة في الـ Node-RED

  updateLED(LED_RED); // اللمبة حمراء

  sendToNodeRED("ERROR:EMERGENCY_STOP_ACTIVATED");
  sendToNodeRED("STATUS:ALL_DISABLED_EXCEPT_HOMING");
  sendToNodeRED("STATUS:SYSTEM_REQUIRES_NEW_HOMING");
}

// ============================================================================
// [11] وظائف تنفيذ البرنامج الآلي (Program Execution Functions)
// ============================================================================

// دالة بدء البرنامج وتنفيذ العمليات على جميع النقاط
void startProgram(String cmd) {
  if (!isHomed) {
    sendToNodeRED("ERROR:START_PROGRAM_NOT_HOMED");
    return;
  }
  if (programRunning) {
    sendToNodeRED("ERROR:PROGRAM_ALREADY_RUNNING");
    return;
  }

  // إذا قام الـ Node-RED بإرسال زوايا في نفس الأمر (مثلاً START_PROGRAM 0 45 90)
  // فإننا نقوم بتفريغ المصفوفة وكتابة هذه الأرقام الجديدة فوقها.
  if (cmd.length() > 14) {
    cmd = cmd.substring(cmd.indexOf(" ") + 1); // قص النص
    cmd.replace(",", " "); // استبدال الفواصل بمسافات
    cmd.replace("|", " "); // استبدال الأعمدة بمسافات

    int idx = 0;
    String temp = "";
    for (unsigned int i = 0; i < cmd.length(); i++) {
      if (cmd[i] == ' ') {
        if (temp.length() > 0 && idx < 30) {
          targetStepsArray[idx++] = temp.toInt();
          temp = "";
        }
      } else {
        temp += cmd[i];
      }
    }
    if (temp.length() > 0 && idx < 30) {
      targetStepsArray[idx++] = temp.toInt();
    }
    totalPositions = idx; // تحديث إجمالي الزوايا بالعدد الجديد
  }

  // إذا لم تكن هناك أي زوايا مخزنة، لا يبدأ البرنامج
  if (totalPositions == 0) {
    sendToNodeRED("ERROR:START_PROGRAM_NO_POSITIONS");
    return;
  }

  // الإعلان عن تشغيل البرنامج - الانتقال لحالة ARMED وانتظار إشارة الروبوت
  programRunning = true;
  programPaused = false;
  pausedCobotFinishedSignal = false;
  currentPositionIndex = 0;

  // إرسال معلومات للواجهة لتعطيل الأزرار اليدوية
  sendToNodeRED("STATUS:CONFIGURATION_LOCKED");
  sendToNodeRED("STATUS:HOLD_ADD_NOW_DISABLED");
  sendToNodeRED("STATUS:PROGRAM_ARMED"); // إبلاغ Node-RED بالتسليح
  sendToNodeRED("STATUS:PROGRAM_STARTED_" + String(totalPositions) +
                "_POSITIONS");

  // *** التغيير الجوهري: لا تتحرك الطاولة الآن، تنتظر إشارة الروبوت ***
  digitalWrite(ENABLE_PIN, LOW);
  currentState = ARMED;
  updateLED(LED_YELLOW); // الإضاءة صفراء لتأكيد توقف المحرك وجاهزيته للحفظ
  sendToNodeRED("STATUS:ARMED_WAITING_FOR_ROBOT_START_SIGNAL");
}

// دالة توجيه المحرك للنقطة المطلوبة الحالية
void moveToCurrentTarget() {
  long targetSteps =
      targetStepsArray[currentPositionIndex]; // سحب الزاوية من المصفوفة
                                              // تحويلها إلى خطوات (Steps)

  stepper.setMaxSpeed(MAX_SPEED * (speedPercentage / 100.0)); // ضبط السرعة القصوى حسب النسبة المحددة من الواجهة
  stepper.setAcceleration(
      PROGRAM_ACCELERATION); // إستخدام تسارع عالي جداً لإلغاء التوقف الناعم
  stepper.moveTo(
      targetSteps); // إرسال الأمر للمحرك للذهاب للموقع (Non-blocking)

  currentState = PROGRAM_MOVING; // تغيير الحالة لـ "يتحرك لتنفيذ النقطة"
  updateLED(LED_BLUE); // تغيير الإضاءة للون الأزرق لتدل على الحركة

  sendToNodeRED("STATUS:MOVING_TO_POSITION_" +
                String(currentPositionIndex + 1));
}

// ============================================================================
// [12] مدير حالات النظام - العقل المدبر (System State Manager)
// ============================================================================

void handleSystemState() {
  switch (currentState) {

  // حالة التصفير (البحث عن نقطة الصفر بدون توقيف النظام)
  case HOMING:
    if (digitalRead(SENSOR_PIN) == SENSOR_HOME_STATE) {
      // المستشعر لقط نقطة الصفر
      stepper.setCurrentPosition(0);
      isHomed = true;
      currentState = IDLE;

      updateLED(LED_GREEN);
      sendToNodeRED("HOMED");
      sendToNodeRED("STATUS:HOME_POSITION_0_STEPS");
      sendToNodeRED("STATUS:READY_FOR_MANUAL_CONFIGURATION");
    } else if (millis() - homingStartTime > HOMING_TIMEOUT_MS) {
      // تجاوز المهلة المحددة
      handleError("HOMING_TIMEOUT");
    }
    break;

  // *** جديد *** انتظار إشارة الروبوت لبدء أو إعادة دورة اللحام
  case ARMED:
    if (digitalRead(RELAY_FROM_COBOT) == LOW) {
      // استُلمت إشارة الروبوت - انتظر 2 ثانية قبل التحريك
      currentPositionIndex = 0;
      sendToNodeRED("STATUS:ROBOT_START_SIGNAL_RECEIVED");
      sendToNodeRED("STATUS:PROGRAM_EXECUTION_STARTED");
      currentState = DELAY_BEFORE_START; // انتظر ثانيتين أولاً
      delayStartTime = millis();
      updateLED(LED_YELLOW);
      sendToNodeRED("STATUS:STARTING_IN_2_SECONDS");
    }
    break;

  // *** جديد *** تأخير 2 ثانية بعد إشارة الروبوت قبل بدء حركة الطاولة
  case DELAY_BEFORE_START:
    if (millis() - delayStartTime >= START_DELAY_MS) {
      moveToCurrentTarget(); // بعد الثانيتين: ابدأ الحركة للوضع الأول
    }
    break;

  case PROGRAM_PAUSED:
    if (pausedState == WAITING_COBOT && !pausedCobotFinishedSignal && digitalRead(RELAY_FROM_COBOT) == LOW) {
      pausedCobotFinishedSignal = true;
      sendToNodeRED("STATUS:COBOT_FINISHED_SIGNAL_STORED_DURING_PAUSE");
    }
    break;

  case MANUAL_MOVING:
    // تحديث الزاوية الحية أثناء الدوران اليدوي
    if (millis() - lastStatusTime >= STATUS_UPDATE_INTERVAL_MS) {
      long currentSteps = stepper.currentPosition();
      sendToNodeRED("STEPS:" + String(currentSteps));
      lastStatusTime = millis();
    }
    break;

  // عند ضغط زر HOLD يبدأ المحرك بالتباطؤ، وبمجرد وصوله لمرحلة التوقف
  // (المسافة=0)
  case MANUAL_DECELERATING:
    if (stepper.distanceToGo() == 0) {
      currentState = MANUAL_HOLD; // تغيير الحالة للتوقف التام
      long currentSteps = stepper.currentPosition();
      updateLED(LED_YELLOW); // الإضاءة صفراء لتأكيد توقف المحرك وجاهزيته للحفظ
      sendToNodeRED("STATUS:MOTOR_STOPPED");
      sendToNodeRED("STATUS:POSITION_CAPTURED_AT_" + String(currentSteps) +
                    "_STEPS");
      sendToNodeRED(
          "STATUS:ADD_BUTTON_NOW_ENABLED"); // إبلاغ المستخدم بضغط زر ADD للحفظ
    }
    break;

  // أثناء حركة البرنامج لزاوية اللحام المطلوبة
  case PROGRAM_MOVING:
    // 1. تحديث وإرسال الزاوية كل 100 ملي ثانية لعرضها في الداشبورد
    if (millis() - lastStatusTime >= STATUS_UPDATE_INTERVAL_MS) {
      long currentSteps = stepper.currentPosition();
      sendToNodeRED("STEPS:" + String(currentSteps));
      lastStatusTime = millis();
    }

    // 2. فحص إذا كان المحرك قد وصل للموقع المطلوب (المسافة المتبقية=0)
    if (stepper.distanceToGo() == 0) {
      long reachedSteps = stepper.currentPosition();
      sendToNodeRED("STATUS:POSITION_" + String(currentPositionIndex + 1) +
                    "_REACHED_" + String(reachedSteps) + "_STEPS");
      // الانتقال للخطوة التالية وهي تشغيل ريلاي الروبوت
      activateRelayToCobot();
    }
    break;

  // أثناء تفعيل الريلاي (إرسال إشارة للروبوت)
  case RELAY_ACTIVE:
    // الانتظار حتى تنقضي ثانية واحدة (1000ms) بالضبط باستخدام millis()
    if (millis() - relayStartTime >= RELAY_PULSE_MS) {
      digitalWrite(RELAY_TO_COBOT, RELAY_TO_COBOT_OFF); // إيقاف الريلاي بعد انتهاء مدة النبضة
      sendToNodeRED("STATUS:RELAY_OFF_TO_COBOT");

      // الانتقال لحالة انتظار إشارة الانتهاء من الروبوت
      currentState = WAITING_COBOT;
      cobotWaitStartTime = millis(); // بدء عداد الـ Timeout (الدقيقتين)
      lastCountdownTime = millis(); // بدء عداد إرسال الرسالة كل ثانية
      sendToNodeRED("STATUS:WAITING_FOR_COBOT_RESPONSE");
    }
    break;

  // أثناء انتظار رد الروبوت بالانتهاء
  case WAITING_COBOT:
    // 1. إذا أرسل الروبوت إشارة الانتهاء (أصبحت LOW بعد التعديل لمنع التشويش)
    if (digitalRead(RELAY_FROM_COBOT) == LOW) {
      currentState = DELAY_BEFORE_MOVE; // تغيير الحالة للانتظار
      delayStartTime = millis(); // بدء عداد الـ 3 ثواني
      updateLED(LED_YELLOW); // الإضاءة صفراء لتأكيد توقف المحرك وجاهزيته للحفظ
      sendToNodeRED("STATUS:COBOT_FINISHED_WAITING_3_SECONDS");
    }
    // 2. التحقق من انتهاء المهلة القصوى لانتظار الروبوت (Timeout - 120 ثانية)
    else if (cobotTimeoutMs > 0 && millis() - cobotWaitStartTime >= cobotTimeoutMs) {
      // إعلان خطأ وإيقاف النظام
      handleError("WELD_TIMEOUT_POSITION_" + String(currentPositionIndex + 1));
    }
    // 3. إرسال عد تنازلي يظهر في الواجهة لتوضيح المهلة المتبقية كل ثانية
    else if (cobotTimeoutMs > 0 && millis() - lastCountdownTime >= COUNTDOWN_UPDATE_INTERVAL_MS) {
      int secondsLeft = (cobotTimeoutMs - (millis() - cobotWaitStartTime)) /
                        1000; // حساب الثواني المتبقية
      sendToNodeRED("STATUS:WAITING_FOR_COBOT_RESPONSE_SECONDS_LEFT:" +
                    String(secondsLeft));
      lastCountdownTime = millis();
    }
    break;

  // حالة انتظار 3 ثواني قبل التحرك للزاوية التالية
  case DELAY_BEFORE_MOVE:
    if (millis() - delayStartTime >= 3000) { // بعد مرور 3 ثواني
      completeWeldPosition(); // إكمال النقطة والانتقال للتالية
    }
    break;

  // حالة الوميض الأخضر السريع (50 ملي ثانية) بعد نجاح نقطة اللحام
  case WELD_COMPLETE_DELAY:
    if (millis() - delayStartTime >= 50) {
      currentPositionIndex++; // الانتقال للفهرس (النقطة) التالية

      // التحقق مما إذا كانت هناك نقاط متبقية في البرنامج
      if (currentPositionIndex < totalPositions) {
        moveToCurrentTarget(); // بعد الثانيتين: ابدأ الحركة للوضع الأول
      } else {
        // انتهت جميع النقاط - العودة للصفر
        sendToNodeRED("STATUS:RETURNING_TO_HOME");
        updateLED(LED_BLUE);

        stepper.setMaxSpeed(MAX_SPEED * (speedPercentage / 100.0));
        stepper.setAcceleration(PROGRAM_ACCELERATION);
        stepper.moveTo(0);

        currentState = RETURNING_HOME; // الانتقال للحالة الجديدة
      }
    }
    break;

  case MANUAL_GO_HOME:
    if (stepper.distanceToGo() == 0) {
      currentState = programPaused ? PROGRAM_PAUSED : IDLE;
      updateLED(programPaused ? LED_YELLOW : LED_GREEN);
      sendToNodeRED("STEPS:0");
      sendToNodeRED("STATUS:RETURNED_TO_HOME_MANUALLY");
    } else if (millis() - lastStatusTime >= STATUS_UPDATE_INTERVAL_MS) {
      long currentSteps = stepper.currentPosition();
      sendToNodeRED("STEPS:" + String(currentSteps));
      lastStatusTime = millis();
    }
    break;

  case MANUAL_GO_TO_POS:
    if (stepper.distanceToGo() == 0) {
      long currentSteps = stepper.currentPosition();
      currentState = programPaused ? PROGRAM_PAUSED : IDLE;
      updateLED(programPaused ? LED_YELLOW : LED_GREEN);
      sendToNodeRED("STEPS:" + String(currentSteps));
      sendToNodeRED("STATUS:GO_TO_POSITION_REACHED");
    } else if (millis() - lastStatusTime >= STATUS_UPDATE_INTERVAL_MS) {
      long currentSteps = stepper.currentPosition();
      sendToNodeRED("STEPS:" + String(currentSteps));
      lastStatusTime = millis();
    }
    break;
  case RETURNING_HOME:
    if (stepper.distanceToGo() == 0) {
      // حالة العودة لنقطة الصفر في نهاية البرنامج (بشكل غير معطل)
      currentState = ARMED;
      updateLED(LED_GREEN);
      sendToNodeRED("STEPS:0");
      sendToNodeRED("STATUS:CYCLE_COMPLETE_PIECE_DONE");
      sendToNodeRED("STATUS:PROGRAM_FINISHED_" + String(totalPositions) + "_OF_" +
                    String(totalPositions) + "_POSITIONS");
      sendToNodeRED("STATUS:ARMED_WAITING_FOR_ROBOT_START_SIGNAL"); // انتظار القطعة الجديدة
    } else {
      // *** بعد العودة للصفر: إعادة التسليح تلقائياً بدون الحاجة لضغط START ***
      if (millis() - lastStatusTime >= STATUS_UPDATE_INTERVAL_MS) {
        long currentSteps = stepper.currentPosition();
        sendToNodeRED("STEPS:" + String(currentSteps));
        lastStatusTime = millis();
      }
    }
    break;

  // إرسال تحديث الخطوات أثناء العودة
  default:
    break;
  }
}

// أي حالة أخرى لا تتطلب تفاعلاً هنا
// ============================================================================
// [13] دوال اللحام المساعدة (Helpers)

// ============================================================================
void activateRelayToCobot() {
  currentState = RELAY_ACTIVE; // تغيير الحالة
  relayStartTime = millis(); // بدء مؤقت الريلاي
  digitalWrite(RELAY_TO_COBOT, RELAY_TO_COBOT_ON); // إرسال إشارة البدء إلى الروبوت عبر تفعيل الريلاي

  updateLED(LED_YELLOW); // الإضاءة صفراء لتأكيد توقف المحرك وجاهزيته للحفظ
  sendToNodeRED("STATUS:RELAY_ON_TO_COBOT");
}

// دالة تفعيل الريلاي للروبوت
void completeWeldPosition() {
  sendToNodeRED("STATUS:WELD_COMPLETE_POSITION_" +
                String(currentPositionIndex + 1));
  updateLED(LED_GREEN); // الإضاءة خضراء لتأكيد الحفظ بنجاح

  currentState = WELD_COMPLETE_DELAY;
  delayStartTime = millis(); // بدء عداد الـ 3 ثواني
}

// دالة اكتمال اللحام في النقطة الحالية وتحديد التالي
void handleError(String errorMsg) {
  handleEmergencyStop(); // إيقاف طوارئ كامل (يدمر أي شيء ويطلب Homing)
                         // دالة إدارة إرسال رسائل الخطأ الشاملة (للطوارئ)
  sendToNodeRED("ERROR:" + errorMsg); // إرسال سبب الخطأ
}

// التصفير للنقاط
void updateLED(uint32_t color) {
  strip.setPixelColor(0, color);
  strip.show();
}

// دالة تحديث اللمبة باللون المطلوب بكل سهولة
void sendToNodeRED(String message) { Serial.println(message); }
