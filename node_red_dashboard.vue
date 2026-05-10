<style>
  .nrdb-layout--notebook[data-v-c88f8420] {
    margin: auto;
    width: 100%;
    max-width: none;
    min-height: 100%;
    flex-wrap: wrap;
    padding: var(--page-padding);
    --layout-columns: var(--v0f9ee0ac);
  }

.v-card-item .v-card-title {
padding: 0;
text-align: center;
font-size: xxx-large;
}
</style>

<template>
  <v-container fluid class="pa-4">
    <v-row>
      
      <!-- ================= LEFT SIDE : POSITION TABLE ================= -->
      <v-col cols="12" md="7">
        <v-card elevation="3" class="pa-4">
          <div class="d-flex justify-space-between align-center mb-4">
             <h2>WELDING POSITIONS</h2>
             <v-chip color="primary" variant="flat">HOME : 0 STEPS</v-chip>
          </div>

          <table class="position-table mt-3" style="width: 100%; text-align: center; border-collapse: collapse;">
            <thead>
              <tr style="background-color: #f5f5f5; border-bottom: 2px solid #ccc;">
                <th style="padding: 12px;">#</th>
                <th style="padding: 12px;">Position Name</th>
                <th style="padding: 12px;">Steps</th>
                <th style="padding: 12px;">Order</th>
                <th style="padding: 12px;">Edit</th>
                <th style="padding: 12px;">Delete</th>
              </tr>
            </thead>
            <tbody>
              <tr v-for="(pos, index) in positions" :key="pos.id" 
                  :style="{ borderBottom: '1px solid #eee', backgroundColor: activePositionIndex === index ? '#bbdefb' : 'transparent' }">
                <td style="padding: 12px; font-weight: bold;">{{ index + 1 }}</td>
                <td style="padding: 12px;">{{ pos.name }}</td>
                <td style="padding: 12px; font-size: 1.2rem; color: #1976d2; font-weight: bold;">
                  <span v-if="!pos.editing">{{ pos.steps }}</span>
                  <v-text-field v-else type="number" density="compact" v-model.number="pos.steps" hide-details></v-text-field>
                </td>
                <td style="padding: 12px;">
                  <!-- Disabled only when program is ACTIVELY running (not just armed) -->
                  <v-btn size="small" icon color="grey-lighten-2" class="mr-1" @click="moveUp(index)" :disabled="index === 0 || isProgramRunning">
                    <v-icon>mdi-arrow-up</v-icon>
                  </v-btn>
                  <v-btn size="small" icon color="grey-lighten-2" @click="moveDown(index)" :disabled="index === positions.length - 1 || isProgramRunning">
                    <v-icon>mdi-arrow-down</v-icon>
                  </v-btn>
                </td>
                <td style="padding: 12px;">
                  <v-btn size="small" :color="pos.editing ? 'orange' : 'green'" @click="toggleEdit(pos)" :disabled="isProgramRunning">
                    {{ pos.editing ? 'SAVE' : 'EDIT' }}
                  </v-btn>
                </td>
                <td style="padding: 12px;">
                  <v-btn size="small" color="red" @click="deletePosition(index)" :disabled="isProgramRunning">
                    <v-icon>mdi-delete</v-icon>
                  </v-btn>
                </td>
              </tr>
              <tr v-if="positions.length === 0">
                <td colspan="6" style="padding: 20px; color: gray;">No positions added yet. Move motor and press ADD.</td>
              </tr>
            </tbody>
          </table>

          <v-row class="mt-4" justify="center">
            <v-col cols="6" sm="4">
              <!-- SAVE to file: always available (doesn't change positions) -->
              <v-btn block color="blue" size="large" @click="saveToFile" :disabled="isProgramRunning">
                <v-icon left>mdi-content-save</v-icon> SAVE
              </v-btn>
            </v-col>
            <v-col cols="6" sm="4">
              <v-btn block color="blue-grey" size="large" @click="loadFromFile" :disabled="isProgramRunning">
                <v-icon left>mdi-folder-open</v-icon> LOAD
              </v-btn>
            </v-col>
          </v-row>
        </v-card>
      </v-col>

      <!-- ================= RIGHT SIDE : CONTROL PANEL ================= -->
      <v-col cols="12" md="5">
        <v-card elevation="3" class="pa-4 text-center">
          
          <h3 class="text-grey-darken-1 mb-2">ACTUAL POSITION (STEPS)</h3>
          <div class="text-h2 font-weight-bold text-success mb-4">{{ currentSteps }}</div>

          <v-alert class="mb-4 text-left" :color="statusColor" variant="tonal" border="start" border-color="primary">
            <strong>Status:</strong> {{ statusText }}
          </v-alert>

          <!-- MANUAL JOGGING: disabled only when program is ACTIVELY running -->
          <v-row dense>
            <v-col cols="6">
              <v-btn block color="orange" size="x-large" @click="moveBackward" :disabled="!isHomed || isProgramRunning || currentSteps <= 0 || isMoving">
                <v-icon left>mdi-minus-box</v-icon> CCW
              </v-btn>
            </v-col>
            <v-col cols="6">
              <v-btn block color="green" size="x-large" @click="moveForward" :disabled="!isHomed || isProgramRunning || isMoving">
                <v-icon left>mdi-plus-box</v-icon> CW
              </v-btn>
            </v-col>
          </v-row>

          <v-btn block class="mt-3" color="brown" size="x-large" @click="holdMotor" :disabled="!isMoving || isProgramRunning">
            <v-icon left>mdi-pause</v-icon> HOLD
          </v-btn>

          <v-row dense class="mt-3">
            <v-col cols="6">
              <v-btn block color="purple" size="x-large" @click="startHoming" :disabled="isMoving || isHoming || isProgramRunning">
                <v-icon left>mdi-crosshairs-gps</v-icon> HOMING
              </v-btn>
            </v-col>
            <v-col cols="6">
              <v-btn block color="blue" size="x-large" @click="saveCurrentPosition" :disabled="isMoving || !isHomed || isProgramRunning">
                <v-icon left>mdi-map-marker-plus</v-icon> ADD
              </v-btn>
            </v-col>
          </v-row>

          <!-- NEW BUTTONS: GO HOME & SET HOME -->
          <v-row dense class="mt-3">
            <v-col cols="6">
              <v-btn block color="teal" size="x-large" @click="goHome" :disabled="isMoving || isHoming || isProgramRunning || !isHomed || currentSteps === 0">
                <v-icon left>mdi-home-import-outline</v-icon> GO HOME
              </v-btn>
            </v-col>
            <v-col cols="6">
              <v-btn block color="indigo" size="x-large" @click="setHomeHere" :disabled="isMoving || isHoming || isProgramRunning">
                <v-icon left>mdi-home-map-marker</v-icon> SET HOME
              </v-btn>
            </v-col>
          </v-row>

          <v-divider class="my-4"></v-divider>

          <!-- EXECUTION -->
          <v-row dense>
            <v-col cols="12" sm="6">
              <!--
                START:
                - Disabled when isArmed (already armed, waiting for robot)
                - Disabled when isProgramRunning (cycle actively running)
                - Re-enabled when user does ANY action while armed (auto-disarm)
              -->
              <v-btn block color="success" size="x-large" @click="startProgram"
                :disabled="positions.length === 0 || !isHomed || isArmed || isProgramRunning">
                <v-icon left>mdi-play-circle</v-icon> START
              </v-btn>
            </v-col>
            <v-col cols="12" sm="6">
              <v-btn block color="red" size="x-large" @click="emergencyStop">
                <v-icon left>mdi-alert-octagon</v-icon> E-STOP
              </v-btn>
            </v-col>
          </v-row>

          <v-divider class="my-4"></v-divider>
          
          <!-- MOTOR SPEED -->
          <h3 class="text-grey-darken-1 mb-2">MOTOR SPEED</h3>
          <v-slider
            v-model="motorSpeed"
            min="10"
            max="100"
            step="5"
            thumb-label="always"
            color="primary"
            track-color="grey-lighten-2"
            @update:model-value="updateSpeed"
            hide-details
          >
            <template v-slot:append>
              <span class="text-h6 font-weight-bold ml-2">{{ motorSpeed }} %</span>
            </template>
          </v-slider>

        </v-card>
      </v-col>

    </v-row>

    <!-- FOOTER -->
    <v-row class="mt-4">
      <v-col cols="12">
        <v-card elevation="2" class="pa-3 text-center" style="background-color: #f8f9fa; border-top: 3px solid #1976d2;">
          <div style="color: #424242; font-size: 1.1rem;">
            <strong>Developed by:</strong> <span style="color: #1976d2; font-weight: bold;">Bayram Alak</span>
            <span class="mx-2">|</span>
            <v-icon size="small" color="primary" class="mr-1">mdi-email</v-icon>
            <a href="mailto:eng.bayram@yahoo.com" style="text-decoration: none; color: #1976d2; font-weight: 500;">eng.bayram@yahoo.com</a>
          </div>
        </v-card>
      </v-col>
    </v-row>

    <!-- SET HOME CONFIRMATION DIALOG -->
    <v-dialog v-model="showHomeDialog" max-width="500">
      <v-card>
        <v-card-title class="text-h5 bg-warning text-white pa-4">
          <v-icon left color="white">mdi-alert</v-icon> Set New Home Position
        </v-card-title>
        <v-card-text class="pa-4 text-h6 text-center">
          You are about to zero the counter and set the new Home (0 steps) to this current physical position.<br><br>
          Are you sure you want to proceed?
        </v-card-text>
        <v-card-actions class="pa-4 justify-center">
          <v-btn color="grey-darken-1" variant="flat" size="large" @click="showHomeDialog = false">CANCEL</v-btn>
          <v-btn color="red" variant="flat" size="large" @click="confirmSetHome">CONFIRM</v-btn>
        </v-card-actions>
      </v-card>
    </v-dialog>

  </v-container>
</template>

<script>
export default {
  data() {
    return {
      currentSteps: 0,
      positions: [],
      nextId: 1,
      isHomed: false,
      isMoving: false,
      isHoming: false,
      isProgramRunning: false,
      // isArmed: true = Arduino is in ARMED state waiting for robot signal.
      // Only the START button is disabled by isArmed.
      // ALL other buttons (CW/CCW/HOLD/ADD/DELETE/EDIT/ORDER/SAVE/LOAD) work normally.
      isArmed: false,
      activePositionIndex: -1, // لمعرفة أي نقطة يتم اللحام عليها حالياً
      motorSpeed: 100, // نسبة سرعة المحرك الافتراضية
      lastSpeedSent: 100, // لتجنب إرسال نفس القيمة عدة مرات
      showHomeDialog: false // للتحكم بظهور نافذة تأكيد الهوم
    }
  },

  computed: {
    statusText() {
      if (this.isArmed)          return "ARMED - Waiting for Robot Start Signal...";
      if (this.isProgramRunning) return "Program Running...";
      if (this.isHoming)         return "Homing in progress...";
      if (!this.isHomed)         return "NOT HOMED - Press HOMING button";
      if (this.isMoving)         return "Motor moving...";
      return "Ready";
    },

    statusColor() {
      if (this.isArmed)          return "purple";
      if (this.isProgramRunning) return "blue";
      if (!this.isHomed)         return "red";
      if (this.isMoving || this.isHoming) return "orange";
      return "green";
    }
  },

  mounted() {
    // إرسال طلب دوري لجلب الحالة الحقيقية من الأردوينو لتجنب فقدان التزامن
    this.statusInterval = setInterval(() => {
      // إصلاح التقطيع: لا نطلب STATUS أثناء حركة الموتور لتخفيف الضغط على السيريال
      if (!this.isMoving && !this.isHoming && !this.isProgramRunning) {
        this.send({ payload: "STATUS" });
      }
    }, 1500);

    // استرجاع النقاط المحفوظة محلياً عند تحديث الصفحة (Refresh)
    const saved = localStorage.getItem('welding_positions');
    if (saved) {
      try {
        this.positions = JSON.parse(saved);
        this.nextId = Math.max(...this.positions.map(p => p.id || 0), 0) + 1;
      } catch(e) {}
    }
  },

  beforeDestroy() {
    if (this.statusInterval) clearInterval(this.statusInterval);
  },

  unmounted() {
    if (this.statusInterval) clearInterval(this.statusInterval);
  },

  watch: {
    positions: {
      deep: true,
      handler(newPos) {
        // حفظ النقاط محلياً لتجنب ضياعها عند عمل Refresh
        localStorage.setItem('welding_positions', JSON.stringify(newPos));
      }
    },
    msg(newMsg) {
      if (!newMsg || !newMsg.payload) return;
      let text = String(newMsg.payload).trim();

      // [1] Structured Parsing (Single Source of Truth)
      // Example: STATUS|HOMED:1|PROG:0|POS:123|STATE:5
      if (text.startsWith("STATUS|")) {
        const parts = text.split('|');
        parts.forEach(part => {
          if (part.startsWith('HOMED:')) this.isHomed = (part.split(':')[1] === '1');
          if (part.startsWith('PROG:'))  this.isProgramRunning = (part.split(':')[1] === '1');
          if (part.startsWith('POS:'))   this.currentSteps = parseInt(part.split(':')[1]);
          if (part.startsWith('STATE:')) {
            const state = parseInt(part.split(':')[1]);
            // States from Arduino: IDLE=0, HOMING=1, MANUAL_MOVING=2, ARMED=5, PROGRAM_MOVING=7, MANUAL_GO_HOME=13
            this.isArmed = (state === 5);
            this.isHoming = (state === 1);
            this.isMoving = (state === 2 || state === 3 || state === 7 || state === 11 || state === 12 || state === 13);
            
            // إصلاح: إذا كان النظام فقط "مسلح" وينتظر الروبوت، يجب فك القفل عن الأزرار
            // ليتمكن المستخدم من الضغط عليها لإلغاء التسليح (Disarm)
            if (this.isArmed) {
              this.isProgramRunning = false;
            }
          }
        });
        return; // توقف هنا، لقد حصلنا على الحالة اليقينية الكاملة
      }

      // [2] Transient UI updates (للأحداث العابرة وتنبيهات الأخطاء السريعة)
      // Arduino restarted
      if (text.startsWith("STATUS:MOVING_TO_POSITION_")) {
        this.activePositionIndex = parseInt(text.substring(26)) - 1;
      }
      
      if (text === "STATUS:RETURNING_TO_HOME" || text === "STATUS:CYCLE_COMPLETE_PIECE_DONE") {
        this.activePositionIndex = -1;
      }

      if (text === "SYSTEM_READY") {
        this.isHomed = false;
        this.activePositionIndex = -1;
        this.isMoving = false;
        this.isHoming = false;
        this.isProgramRunning = false;
        this.isArmed = false;
        this.currentSteps = 0;
      }

      if (text.startsWith("STEPS:")) {
        this.currentSteps = parseInt(text.substring(6));
      }

      if (text === "HOMED" || text === "STATUS:HOME_POSITION_0_STEPS") {
        this.isHomed = true;
        this.isHoming = false;
        this.isArmed = false;
        this.currentSteps = 0;
        this.activePositionIndex = -1;
      }

      if (text === "STATUS:MOTOR_STOPPED" || 
          text === "STATUS:MOTOR_STOPPED_AT_ZERO" || 
          text === "STATUS:RETURNED_TO_HOME_MANUALLY") {
        this.isMoving = false;
      }

      // Arduino confirmed it is armed and waiting for robot signal
      // (happens after START pressed, or after each cycle completes automatically)
      if (text === "STATUS:PROGRAM_ARMED" ||
          text === "STATUS:ARMED_WAITING_FOR_ROBOT_START_SIGNAL") {
        this.isArmed = true;
        this.isProgramRunning = false;
      }

      // Robot sent its start signal → cycle actively running → lock ALL buttons
      if (text === "STATUS:PROGRAM_EXECUTION_STARTED" ||
          text === "STATUS:ROBOT_START_SIGNAL_RECEIVED") {
        this.isArmed = false;
        this.isProgramRunning = true;
      }

      // One cycle finished, Arduino re-armed itself → buttons available again
      if (text === "STATUS:CYCLE_COMPLETE_PIECE_DONE") {
        this.isProgramRunning = false;
        // isArmed will be set true by the next ARMED_WAITING message from Arduino
      }

      // Arduino confirmed disarm (user took action while armed)
      if (text === "STATUS:DISARMED_BY_OPERATOR" ||
          text === "STATUS:CONFIGURATION_UNLOCKED") {
        this.isArmed = false;
        this.isProgramRunning = false;
      }

      // E-STOP or error resets everything
      if (text === "STATUS:SYSTEM_REQUIRES_NEW_HOMING") {
        this.isProgramRunning = false;
        this.isArmed = false;
      }

      if (text.startsWith("ERROR:")) {
        this.isHoming = false;
        this.isMoving = false;
        this.isProgramRunning = false;
        this.isArmed = false;
      }
    }
  },

  methods: {
    // ---------------------------------------------------------------
    // disarmIfArmed: Called before ANY user action.
    // If the system is currently ARMED, sends DISARM to Arduino and
    // clears isArmed locally → forces user to press START again.
    // ---------------------------------------------------------------
    disarmIfArmed() {
      if (this.isArmed) {
        this.send({ payload: "DISARM" });
        this.isArmed = false;
      }
    },

    saveCurrentPosition() {
      if (!this.isHomed)    { alert("Must press HOMING first!");                  return; }
      if (this.isMoving)    { alert("Stop the motor first (press HOLD)"); return; }
      if (this.isProgramRunning) { return; }

      this.disarmIfArmed(); // If armed → disarm first, user must press START again

      const newPos = {
        id: this.nextId++,
        name: "POS " + (this.positions.length + 1),
        steps: this.currentSteps,
        editing: false
      };
      this.positions.push(newPos);
      this.send({ payload: "ADD" });
    },

    deletePosition(index) {
      if (this.isProgramRunning) { return; }
      if (confirm("Delete this position?")) {
        this.disarmIfArmed(); // Positions changed → must re-arm
        this.positions.splice(index, 1);
      }
    },

    toggleEdit(pos) {
      if (this.isProgramRunning) { return; }
      if (pos.editing) {
        // User is saving an edit → التحقق من صحة الرقم أولاً
        const parsedSteps = parseInt(pos.steps);
        if (isNaN(parsedSteps) || parsedSteps < 0) {
          alert("The number of steps must be positive and correct.");
          return; // منع الحفظ
        }
        if (parsedSteps > 500000) {
          alert("The number of steps is too large (maximum 500,000 steps).");
          return; // منع الحفظ
        }
        pos.steps = parsedSteps; // حفظ الرقم النظيف
        
        // positions changed → disarm
        this.disarmIfArmed();
      }
      pos.editing = !pos.editing;
    },

    moveUp(index) {
      if (index === 0 || this.isProgramRunning) return;
      this.disarmIfArmed(); // Reordering is a change → disarm
      const temp = this.positions[index];
      this.positions.splice(index, 1);
      this.positions.splice(index - 1, 0, temp);
    },

    moveDown(index) {
      if (index === this.positions.length - 1 || this.isProgramRunning) return;
      this.disarmIfArmed(); // Reordering is a change → disarm
      const temp = this.positions[index];
      this.positions.splice(index, 1);
      this.positions.splice(index + 1, 0, temp);
    },

    moveForward() {
      if (!this.isHomed) { alert("Must press HOMING first!"); return; }
      if (this.isProgramRunning) { return; }
      // If ARMED: only disarm (cancel waiting for robot), do NOT move motor.
      // Motor movement only works in normal IDLE state.
      if (this.isArmed) { this.disarmIfArmed(); return; }
      this.isMoving = true;
      this.send({ payload: "MOVE_FORWARD" });
    },

    moveBackward() {
      if (!this.isHomed) { alert("Must press HOMING first!"); return; }
      if (this.currentSteps <= 0) { alert("Cannot move below zero!"); return; }
      if (this.isProgramRunning) { return; }
      // If ARMED: only disarm (cancel waiting for robot), do NOT move motor.
      // Motor movement only works in normal IDLE state.
      if (this.isArmed) { this.disarmIfArmed(); return; }
      this.isMoving = true;
      this.send({ payload: "MOVE_BACKWARD" });
    },

    holdMotor() {
      if (this.isProgramRunning) { return; }
      this.disarmIfArmed();
      this.isMoving = false;
      this.send({ payload: "HOLD" });
    },

    startHoming() {
      if (this.isMoving) { alert("Stop motor first (press HOLD)"); return; }
      if (this.isProgramRunning) { return; }
      this.disarmIfArmed(); // Homing while armed → disarm
      this.isHoming = true;
      this.send({ payload: "HOMING" });
    },

    goHome() {
      if (!this.isHomed) { alert("System must be homed first!"); return; }
      if (this.currentSteps === 0) { return; }
      if (this.isProgramRunning) { return; }
      if (this.isArmed) { this.disarmIfArmed(); } // Disarm but continue to move
      
      this.isMoving = true;
      this.send({ payload: "GO_HOME" });
    },

    setHomeHere() {
      if (this.isMoving || this.isHoming || this.isProgramRunning) return;
      this.showHomeDialog = true; // إظهار النافذة المنبثقة الخاصة بـ Vuetify
    },

    confirmSetHome() {
      this.showHomeDialog = false;
      this.disarmIfArmed(); // Disarm if it was armed
      this.send({ payload: "SET_HOME_HERE" });
    },

    emergencyStop() {
      this.isHomed = false;
      this.isMoving = false;
      this.isHoming = false;
      this.isProgramRunning = false;
      this.isArmed = false;
      this.currentSteps = 0;
      this.activePositionIndex = -1;
      // تم إزالة مسح النقاط من هنا للحفاظ عليها كما هي في الأردوينو
      this.send({ payload: "ESTOP" });
    },

    startProgram() {
      if (this.positions.length === 0) { alert("No positions saved!"); return; }
      if (!this.isHomed)               { alert("Must press HOMING first!");    return; }
      if (this.isArmed || this.isProgramRunning) { return; }

      const confirmation = confirm(
        `Start program with ${this.positions.length} positions?\n\nTable will wait for robot signal before moving.`
      );
      if (confirmation) {
        let stepList = this.positions.map(p => p.steps).join(" ");
        this.send({ payload: "START_PROGRAM " + stepList });
      }
    },

    saveToFile() {
      // Saving to file does NOT change positions, so no disarm needed
      const data = { timestamp: new Date().toISOString(), positions: this.positions };
      const dataStr = JSON.stringify(data, null, 2);
      const dataBlob = new Blob([dataStr], { type: 'application/json' });
      const url = URL.createObjectURL(dataBlob);
      const link = document.createElement('a');
      link.href = url;
      link.download = `turntable_positions_${new Date().getTime()}.json`;
      link.click();
    },

    loadFromFile() {
      if (this.isProgramRunning) { return; }
      const input = document.createElement('input');
      input.type = 'file';
      input.accept = '.json';
      input.onchange = (e) => {
        const file = e.target.files[0];
        if (file) {
          const reader = new FileReader();
          reader.onload = (event) => {
            try {
              const data = JSON.parse(event.target.result);
              if (data.positions && Array.isArray(data.positions)) {
                this.disarmIfArmed(); // Loading new positions → must re-arm
                this.positions = data.positions;
                this.nextId = Math.max(...this.positions.map(p => p.id || 0)) + 1;
              } else { alert("Invalid file format!"); }
            } catch (err) { alert("Error reading file: " + err.message); }
          };
          reader.readAsText(file);
        }
      };
      input.click();
    },

    updateSpeed(val) {
      if (val !== this.lastSpeedSent) {
        this.send({ payload: "SET_SPEED " + val });
        this.lastSpeedSent = val;
      }
    }
  }
}
</script>
