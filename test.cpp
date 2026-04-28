#include <Arduino.h>

// رقم المنفذ للمبة الموجودة على لوحة الأردوينو (للاختبار)
const int LED_PIN = 13;

void setup() {
    // 1. فتح الاتصال التسلسلي (Serial) بسرعة 9600
    Serial.begin(9600);
    Serial.setTimeout(50); // تسريع الاستجابة

    // 2. إعداد لمبة الأردوينو كمخرج
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // 3. إرسال رسالة ترحيبية لـ Node-RED عند بدء التشغيل
    Serial.println("ARDUINO_READY: Hello Node-RED!");
}

void loop() {
    // 4. التحقق مما إذا كان هناك رسالة قادمة من Node-RED
    if (Serial.available() > 0) {
        // قراءة الرسالة حتى نهايتها
        String incomingMessage = Serial.readStringUntil('\n');
        incomingMessage.trim(); // تنظيف المسافات

        if (incomingMessage.length() > 0) {
            // إضاءة اللمبة دلالة على استلام رسالة
            digitalWrite(LED_PIN, HIGH);
            
            // 5. الرد على Node-RED لتأكيد الاستلام
            Serial.print("ARDUINO_RECEIVED: ");
            Serial.println(incomingMessage);

            // تأخير بسيط لإبقاء اللمبة مضاءة قليلاً لتلاحظها
            delay(100); 
            digitalWrite(LED_PIN, LOW); // إطفاء اللمبة
        }
    }
}
