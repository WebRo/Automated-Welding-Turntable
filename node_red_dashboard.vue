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


.v-btn.v-btn--disabled,
.v-btn[disabled] {
  opacity: 0.38 !important;
  filter: grayscale(55%) saturate(45%) brightness(1.08);
  box-shadow: none !important;
  cursor: not-allowed !important;
}

.v-btn.v-btn--disabled *,
.v-btn[disabled] * {
  cursor: not-allowed !important;
}
.actual-position-header {
  flex-wrap: wrap;
}

.actual-position-heading {
  display: flex;
  align-items: baseline;
  gap: 12px;
  flex-wrap: wrap;
}

.actual-position-value {
  line-height: 1;
  font-size: 1.25rem;
  color: #4caf50;
}

.actual-position-header .timeout-control {
  margin-left: auto;
}

.timeout-control .timeout-chip {
  min-height: 48px;
  padding: 0 20px;
  border-radius: 4px;
  font-size: 1rem;
  font-weight: 800;
  line-height: 1.2;
  text-transform: uppercase;
  letter-spacing: 0.0892857143em;
  box-shadow: 0 3px 1px -2px rgba(0,0,0,.2), 0 2px 2px 0 rgba(0,0,0,.14), 0 1px 5px 0 rgba(0,0,0,.12);
}

.timeout-control .timeout-select .v-field {
  min-height: 48px;
  border-radius: 4px;
  background-color: #1976d2;
  color: white;
  font-size: 1rem;
  font-weight: 800;
  line-height: 1.2;
  text-transform: uppercase;
  letter-spacing: 0.0892857143em;
  box-shadow: 0 3px 1px -2px rgba(0,0,0,.2), 0 2px 2px 0 rgba(0,0,0,.14), 0 1px 5px 0 rgba(0,0,0,.12);
}

.timeout-control .timeout-select .v-field__input,
.timeout-control .timeout-select .v-select__selection-text,
.timeout-control .timeout-select .v-icon {
  color: white;
  font-weight: 800;
  line-height: 1.2;
  text-transform: uppercase;
  letter-spacing: 0.0892857143em;
}


.timeout-control .timeout-chip .v-chip__content,
.timeout-control .timeout-select .v-select__selection-text,
.timeout-control .timeout-select input {
  font-size: 1rem !important;
  font-weight: 800 !important;
  line-height: 1.2 !important;
  text-transform: uppercase !important;
  letter-spacing: 0.0892857143em !important;
}

.timeout-control .timeout-select .v-field__input {
  min-height: 48px;
  padding-top: 0;
  padding-bottom: 0;
}
.position-row-inactive {
  background-color: #eeeeee !important;
  color: #8a8a8a;
}

.position-row-inactive td {
  opacity: 0.72;
}

.position-status-btn {
  min-width: 92px;
  border-radius: 4px;
  font-weight: 800;
}

.pieces-counter-control {
  gap: 10px;
  flex-wrap: wrap;
}

.pieces-counter-chip {
  min-height: 48px;
  border-radius: 4px;
  padding: 0 20px;
  font-size: 1rem;
  font-weight: 800;
  letter-spacing: 0;
  box-shadow: 0 3px 1px -2px rgba(0,0,0,.2), 0 2px 2px 0 rgba(0,0,0,.14), 0 1px 5px 0 rgba(0,0,0,.12);
}

.pieces-reset-btn {
  min-height: 40px;
  border-radius: 4px;
  font-weight: 800;
}

.timeout-control.timeout-control .timeout-chip .v-chip__content,
.timeout-control.timeout-control .timeout-select .v-field,
.timeout-control.timeout-control .timeout-select .v-field__input,
.timeout-control.timeout-control .timeout-select .v-select__selection,
.timeout-control.timeout-control .timeout-select .v-select__selection-text,
.timeout-control.timeout-control .timeout-select input,
.timeout-control.timeout-control .timeout-select .v-icon {
  font-family: Roboto, sans-serif !important;
  font-size: 1rem !important;
  font-weight: 500 !important;
  line-height: 2.75rem !important;
  letter-spacing: 0.0892857143em !important;
  text-indent: 0.0892857143em !important;
  text-transform: uppercase !important;
}

.timeout-control.timeout-control .timeout-chip .v-chip__content,
.timeout-control.timeout-control .timeout-select .v-select__selection-text {
  display: inline-flex !important;
  align-items: center !important;
}

.pieces-counter-control.pieces-counter-control .pieces-counter-chip .v-chip__content,
.pieces-counter-control.pieces-counter-control .pieces-reset-btn .v-btn__content {
  font-family: Roboto, sans-serif !important;
  font-size: 1rem !important;
  font-weight: 500 !important;
  line-height: 2.75rem !important;
  letter-spacing: 0.0892857143em !important;
  text-indent: 0.0892857143em !important;
  text-transform: uppercase !important;
}

.pieces-counter-control.pieces-counter-control .pieces-counter-chip .v-chip__content,
.pieces-counter-control.pieces-counter-control .pieces-reset-btn .v-btn__content {
  display: inline-flex !important;
  align-items: center !important;
}

.language-selector-bar {
  display: flex;
  justify-content: flex-end;
  align-items: center;
  margin-bottom: 12px;
  gap: 10px;
}

.language-selector-label {
  font-weight: 700;
  color: #424242;
  font-size: 1rem;
}

.language-selector-btn {
  min-width: 84px !important;
  height: 42px !important;
  border-radius: 4px !important;
  background: #ffffff !important;
  box-shadow: 0 2px 8px rgba(0,0,0,.16) !important;
}

.language-menu-card {
  min-width: 86px;
  border-radius: 4px !important;
  overflow: hidden;
}

.language-menu-item {
  justify-content: center;
  min-height: 44px !important;
}

.language-flag {
  display: inline-block;
  width: 32px;
  height: 22px;
  border-radius: 3px;
  border: 1px solid rgba(0,0,0,.22);
  box-shadow: 0 1px 2px rgba(0,0,0,.18);
}

.flag-en {
  background:
    linear-gradient(#b22234 0 7.69%, #fff 7.69% 15.38%, #b22234 15.38% 23.07%, #fff 23.07% 30.76%, #b22234 30.76% 38.45%, #fff 38.45% 46.14%, #b22234 46.14% 53.83%, #fff 53.83% 61.52%, #b22234 61.52% 69.21%, #fff 69.21% 76.9%, #b22234 76.9% 84.59%, #fff 84.59% 92.28%, #b22234 92.28% 100%);
  position: relative;
}

.flag-en::before {
  content: "";
  position: absolute;
  left: 0;
  top: 0;
  width: 44%;
  height: 54%;
  background: #3c3b6e;
}

.flag-de { background: linear-gradient(#000 0 33%, #dd0000 33% 66%, #ffce00 66%); }
.flag-ro { background: linear-gradient(90deg, #002b7f 0 33%, #fcd116 33% 66%, #ce1126 66%); }
.flag-ar { background: linear-gradient(#ce1126 0 33%, #fff 33% 66%, #000 66%); }
.flag-pl { background: linear-gradient(#fff 0 50%, #dc143c 50%); }
</style>

<template>
  <v-container fluid class="pa-4">
    <div class="language-selector-bar">
      <span class="language-selector-label">{{ tr("chooseLanguage") }}</span>
      <v-menu location="bottom end">
        <template v-slot:activator="{ props }">
          <v-btn v-bind="props" class="language-selector-btn" variant="flat">
            <span class="language-flag" :class="currentLanguageFlagClass"></span>
            <v-icon size="small" class="ml-1">mdi-chevron-down</v-icon>
          </v-btn>
        </template>
        <v-card class="language-menu-card">
          <v-list density="compact">
            <v-list-item
              v-for="language in languageOptions"
              :key="language.code"
              class="language-menu-item"
              @click="selectedLanguage = language.code"
            >
              <span class="language-flag" :class="language.flagClass"></span>
            </v-list-item>
          </v-list>
        </v-card>
      </v-menu>
    </div>
    <v-row>

      <!-- ================= LEFT SIDE : POSITION TABLE ================= -->
      <v-col cols="12" md="7">
        <v-card elevation="3" class="pa-4">
          <div class="d-flex justify-space-between align-center mb-4" style="gap: 12px; flex-wrap: wrap;">
             <h2>{{ tr("weldingPositions") }}</h2>
             <div class="d-flex align-center pieces-counter-control">
               <v-chip class="pieces-counter-chip" color="blue-grey" variant="flat">
                 {{ tr("weldedPieces") }} : {{ weldedPieces }}
               </v-chip>
               <v-btn
                 class="pieces-reset-btn"
                 :color="weldedPieces > 0 ? 'red' : 'grey'"
                 variant="flat"
                 size="small"
                 :disabled="weldedPieces === 0"
                 @click="resetWeldedPieces"
               >
                 RESET
               </v-btn>
             </div>
          </div>

          <table class="position-table mt-3" style="width: 100%; text-align: center; border-collapse: collapse;">
            <thead>
              <tr style="background-color: #f5f5f5; border-bottom: 2px solid #ccc;">
                <th style="padding: 12px;">#</th>
                <th style="padding: 12px;">{{ tr("positionName") }}</th>
                <th style="padding: 12px;">{{ tr("steps") }}</th>
                <th style="padding: 12px;">{{ tr("status") }}</th>
                <th style="padding: 12px;">{{ tr("order") }}</th>
                <th style="padding: 12px;">{{ tr("edit") }}</th>
                <th style="padding: 12px;">{{ tr("delete") }}</th>
              </tr>
            </thead>
            <tbody>
              <tr v-for="(pos, index) in positions" :key="pos.id"
                  :class="{ 'position-row-inactive': pos.active === false }"
                  :style="{ borderBottom: '1px solid #eee', backgroundColor: activePositionIndex === index ? '#bbdefb' : (pos.active === false ? '#eeeeee' : 'transparent') }">
                <td style="padding: 12px; font-weight: bold;">{{ index + 1 }}</td>
                <td style="padding: 12px;">{{ pos.name }}</td>
                <td :style="{ padding: '12px', fontSize: '1.2rem', color: pos.active === false ? '#777' : '#1976d2', fontWeight: 'bold' }">
                  <span v-if="!pos.editing">{{ pos.steps }}</span>
                  <v-text-field v-else type="number" density="compact" v-model.number="pos.steps" hide-details></v-text-field>
                </td>
                <td style="padding: 12px;">
                  <v-btn
                    size="small"
                    icon
                    class="position-status-btn"
                    :color="pos.active === false ? 'grey' : 'green'"
                    variant="flat"
                    @click="togglePositionActive(pos)"
                    :disabled="isProgramRunning"
                  >
                    <v-icon>{{ pos.active === false ? 'mdi-lock' : 'mdi-lock-open-variant' }}</v-icon>
                  </v-btn>
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
                  <v-btn size="small" :color="pos.editing ? 'orange' : 'light-blue'" @click="toggleEdit(pos)" :disabled="isProgramRunning">
                    <v-icon>{{ pos.editing ? 'mdi-content-save' : 'mdi-pencil' }}</v-icon>
                  </v-btn>
                </td>
                <td style="padding: 12px;">
                  <v-btn size="small" color="red" @click="deletePosition(index)" :disabled="isProgramRunning">
                    <v-icon>mdi-delete</v-icon>
                  </v-btn>
                </td>
              </tr>
              <tr v-if="positions.length === 0">
                <td colspan="7" style="padding: 20px; color: gray;">{{ tr("noPositions") }}</td>
              </tr>
            </tbody>
          </table>

          <v-row class="mt-4" justify="center">
            <v-col cols="6" sm="4">
              <!-- SAVE to file: always available (doesn't change positions) -->
              <v-btn block color="blue" size="large" @click="saveToFile" :disabled="isProgramRunning">
                <v-icon left>mdi-content-save</v-icon> {{ tr("save") }}
              </v-btn>
            </v-col>
            <v-col cols="6" sm="4">
              <v-btn block color="blue-grey" size="large" @click="loadFromFile" :disabled="isProgramRunning">
                <v-icon left>mdi-folder-open</v-icon> {{ tr("load") }}
              </v-btn>
            </v-col>
          </v-row>
        </v-card>
      </v-col>

      <!-- ================= RIGHT SIDE : CONTROL PANEL ================= -->
      <v-col cols="12" md="5">
        <v-card elevation="3" class="pa-4 text-center">

          <div class="d-flex justify-space-between align-center mb-2 actual-position-header" style="gap: 12px;">
            <div class="actual-position-heading">
              <h3 class="text-grey-darken-1 ma-0">{{ tr("actualPosition") }}</h3>
              <div class="font-weight-bold actual-position-value">{{ currentSteps }}</div>
            </div>
            <div class="d-flex align-center timeout-control" style="gap: 12px;">
              <v-chip class="timeout-chip" :color="cobotTimeoutChipColor" variant="flat">
                {{ cobotTimeoutDisplay }}
              </v-chip>
              <v-select
                v-model="cobotTimeoutSetting"
                :items="cobotTimeoutOptions"
                item-title="label"
                item-value="value"
                density="compact"
                hide-details
                variant="outlined"
                class="timeout-select"
                style="max-width: 170px;"
                @update:model-value="sendCobotTimeout"
              ></v-select>
            </div>
          </div>

          <v-alert class="mt-4 mb-4 text-left" :color="statusColor" variant="tonal" border="start" border-color="primary">
            <strong>{{ tr("status") }}:</strong> {{ statusText }}
          </v-alert>

          <!-- MANUAL JOGGING: disabled only when program is ACTIVELY running -->
          <v-row dense>
            <v-col cols="6">
              <v-btn block color="orange" size="x-large" @click="moveBackward" :disabled="!isHomed || (isProgramRunning && !isProgramPaused) || currentSteps <= 0 || isMoving">
                <v-icon left>mdi-minus-box</v-icon> CCW
              </v-btn>
            </v-col>
            <v-col cols="6">
              <v-btn block color="green" size="x-large" @click="moveForward" :disabled="!isHomed || (isProgramRunning && !isProgramPaused) || isMoving">
                <v-icon left>mdi-plus-box</v-icon> CW
              </v-btn>
            </v-col>
          </v-row>

          <v-row dense class="mt-3">
            <v-col cols="6">
              <v-btn block color="brown" size="x-large" @click="holdMotor" :disabled="!isMoving || (isProgramRunning && !isProgramPaused)">
                <v-icon left>mdi-pause</v-icon> HOLD
              </v-btn>
            </v-col>
            <v-col cols="6">
              <v-btn block color="blue" size="x-large" @click="saveCurrentPosition" :disabled="isMoving || !isHomed || isProgramRunning">
                <v-icon left>mdi-map-marker-plus</v-icon> ADD
              </v-btn>
            </v-col>
          </v-row>

          <v-row dense class="mt-3">
            <v-col cols="6">
              <v-btn block color="purple" size="x-large" @click="startHoming" :disabled="isMoving || isHoming || isProgramRunning">
                <v-icon left>mdi-crosshairs-gps</v-icon> {{ tr("homing") }}
              </v-btn>
            </v-col>
            <v-col cols="6">
              <v-btn block :color="isProgramPaused ? 'green' : 'amber'" size="x-large" @click="toggleProgramPause"
                :disabled="!isArmed && !isProgramRunning && !isProgramPaused">
                <v-icon left>{{ isProgramPaused ? 'mdi-play' : 'mdi-pause-circle' }}</v-icon> {{ isProgramPaused ? 'CONTINUE' : 'PAUSE' }}
              </v-btn>
            </v-col>
          </v-row>

          <!-- NEW BUTTONS: GO HOME & SET HOME -->
          <v-row dense class="mt-3">
            <v-col cols="6">
              <v-btn block color="teal" size="x-large" @click="goHome" :disabled="isMoving || isHoming || (isProgramRunning && !isProgramPaused) || !isHomed || currentSteps === 0">
                <v-icon left>mdi-home-import-outline</v-icon> {{ tr("goHome") }}
              </v-btn>
            </v-col>
            <v-col cols="6">
              <v-btn block color="indigo" size="x-large" @click="setHomeHere" :disabled="isMoving || isHoming || isProgramRunning">
                <v-icon left>mdi-home-map-marker</v-icon> {{ tr("setHome") }}
              </v-btn>
            </v-col>
          </v-row>

          <v-row dense class="mt-3">
            <v-col cols="6">
              <v-btn block color="cyan-darken-2" size="x-large" @click="openGoToPosDialog" :disabled="!canGoToPos">
                <v-icon left>mdi-map-marker-path</v-icon> {{ tr("goToPos") }}
              </v-btn>
            </v-col>
            <v-col cols="6">
              <v-btn block color="deep-orange" size="x-large" @click="stopProgramKeepHome" :disabled="!isProgramRunning || isProgramPaused">
                <v-icon left>mdi-stop-circle</v-icon> STOP
              </v-btn>
            </v-col>
          </v-row>

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
                <v-icon left>mdi-play-circle</v-icon> {{ tr("start") }}
              </v-btn>
            </v-col>
            <v-col cols="12" sm="6">
              <v-btn block color="red" size="x-large" @click="emergencyStop">
                <v-icon left>mdi-alert-octagon</v-icon> E-STOP
              </v-btn>
            </v-col>
          </v-row>

          <!-- MOTOR SPEED -->
          <h3 class="text-grey-darken-1 mt-6 mb-2">{{ tr("motorSpeed") }}</h3>
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
          <v-icon left color="white">mdi-alert</v-icon> {{ tr("setNewHomePosition") }}
        </v-card-title>
        <v-card-text class="pa-4 text-h6 text-center">
          {{ tr("setHomeMessage") }}<br><br>
          {{ tr("areYouSure") }}
        </v-card-text>
        <v-card-actions class="pa-4 justify-center">
          <v-btn color="grey-darken-1" variant="flat" size="large" @click="showHomeDialog = false">{{ tr("cancel") }}</v-btn>
          <v-btn color="red" variant="flat" size="large" @click="confirmSetHome">{{ tr("confirm") }}</v-btn>
        </v-card-actions>
      </v-card>
    </v-dialog>

    <!-- START PROGRAM CONFIRMATION DIALOG -->
    <v-dialog v-model="showStartDialog" max-width="560">
      <v-card>
        <v-card-title class="text-h5 bg-success text-white pa-4">
          <v-icon left color="white">mdi-play-circle</v-icon> {{ tr("startProgram") }}
        </v-card-title>
        <v-card-text class="pa-5 text-h6 text-center">
          {{ tr("startProgramWith") }} <strong>{{ pendingStartPositionCount }}</strong> {{ tr("activePositions") }}?<br><br>
          {{ tr("inactiveSkipped") }}
        </v-card-text>
        <v-card-actions class="pa-4 justify-center">
          <v-btn color="grey-darken-1" variant="flat" size="large" @click="cancelStartProgram">{{ tr("cancel") }}</v-btn>
          <v-btn color="success" variant="flat" size="large" @click="confirmStartProgram">OK</v-btn>
        </v-card-actions>
      </v-card>
    </v-dialog>


    <!-- GO TO POSITION DIALOG -->
    <v-dialog v-model="showGoToPosDialog" max-width="650">
      <v-card>
        <v-card-title class="text-h5 bg-cyan-darken-2 text-white pa-4">
          <v-icon left color="white">mdi-map-marker-path</v-icon> {{ tr("goToPosition") }}
        </v-card-title>
        <v-card-text class="pa-4">
          <v-row dense align="center">
            <v-col cols="8">
              <v-select
                v-model="selectedGoToPositionId"
                :items="goToPositionItems"
                item-title="label"
                item-value="id"
                :label="tr('selectPosition')"
                variant="outlined"
                hide-details
              ></v-select>
            </v-col>
            <v-col cols="4">
              <v-btn block color="success" size="x-large" @click="goToSelectedPosition" :disabled="!selectedGoToPositionId || !canGoToPos">
                <v-icon left>mdi-play</v-icon> GO
              </v-btn>
            </v-col>
          </v-row>
        </v-card-text>
        <v-card-actions class="pa-4 justify-center">
          <v-btn color="grey-darken-1" variant="flat" size="large" @click="closeGoToPosDialog">{{ tr("close") }}</v-btn>
        </v-card-actions>
      </v-card>
    </v-dialog>
  </v-container>
</template>

<script>
export default {
  data() {
    return {
      selectedLanguage: "en",
      languageOptions: [
        { code: "en", flagClass: "flag-en" },
        { code: "de", flagClass: "flag-de" },
        { code: "ro", flagClass: "flag-ro" },
        { code: "ar", flagClass: "flag-ar" },
        { code: "pl", flagClass: "flag-pl" }
      ],
      translations: {
        en: {
          chooseLanguage: "Choose language",
          weldingPositions: "WELDING POSITIONS",
          weldedPieces: "WELDED PIECES",
          positionName: "Position Name",
          steps: "Steps",
          status: "Status",
          order: "Order",
          edit: "Edit",
          delete: "Delete",
          noPositions: "No positions added yet. Move motor and press ADD.",
          actualPosition: "ACTUAL POSITION (STEPS)",
          motorSpeed: "MOTOR SPEED",
          setNewHomePosition: "Set New Home Position",
          setHomeMessage: "You are about to zero the counter and set the new Home (0 steps) to this current physical position.",
          areYouSure: "Are you sure you want to proceed?",
          confirm: "CONFIRM",
          startProgram: "Start Program",
          startProgramWith: "Start program with",
          activePositions: "active positions",
          inactiveSkipped: "Inactive positions will be skipped.",
          goToPosition: "Go To Position",
          selectPosition: "Select Position",
          save: "SAVE",
          load: "LOAD",
          homing: "HOMING",
          goHome: "GO HOME",
          setHome: "SET HOME",
          goToPos: "GO TO POS",
          start: "START",
          close: "CLOSE",
          cancel: "CANCEL",
          cobotTimeoutNone: "COBOT TIMEOUT : none",
          errorIn: "ERROR IN",
          programPaused: "Program Paused - Press CONTINUE to resume",
          armedWaiting: "ARMED - Waiting for Robot Start Signal...",
          programRunning: "Program Running...",
          homingProgress: "Homing in progress...",
          notHomed: "NOT HOMED - Press HOMING button",
          motorMoving: "Motor moving...",
          ready: "Ready",
          mustHomeFirst: "Must press HOMING first!",
          stopMotorFirstHold: "Stop the motor first (press HOLD)",
          deletePosition: "Delete this position?",
          invalidSteps: "The number of steps must be positive and correct.",
          stepsTooLarge: "The number of steps is too large (maximum 500,000 steps).",
          cannotMoveBelowZero: "Cannot move below zero!",
          stopMotorFirst: "Stop motor first (press HOLD)",
          systemMustBeHomed: "System must be homed first!",
          noPositionsSaved: "No positions saved!",
          noActivePositions: "No active positions selected!",
          invalidFile: "Invalid file format!",
          errorReadingFile: "Error reading file"
        },
        de: {
          chooseLanguage: "Sprache wählen",
          weldingPositions: "SCHWEISSPOSITIONEN",
          weldedPieces: "GESCHWEISSTE TEILE",
          positionName: "Positionsname",
          steps: "Schritte",
          status: "Status",
          order: "Reihenfolge",
          edit: "Bearbeiten",
          delete: "Löschen",
          noPositions: "Noch keine Positionen hinzugefügt. Motor bewegen und ADD drücken.",
          actualPosition: "AKTUELLE POSITION (SCHRITTE)",
          motorSpeed: "MOTORGESCHWINDIGKEIT",
          setNewHomePosition: "Neue Home-Position setzen",
          setHomeMessage: "Der Zähler wird auf Null gesetzt und die aktuelle physische Position als Home (0 Schritte) gespeichert.",
          areYouSure: "Möchten Sie fortfahren?",
          confirm: "BESTÄTIGEN",
          startProgram: "Programm starten",
          startProgramWith: "Programm starten mit",
          activePositions: "aktiven Positionen",
          inactiveSkipped: "Inaktive Positionen werden übersprungen.",
          goToPosition: "Zur Position fahren",
          selectPosition: "Position wählen",
          save: "SPEICHERN",
          load: "LADEN",
          homing: "HOMING",
          goHome: "ZURÜCK ZU HOME",
          setHome: "HOME SETZEN",
          goToPos: "ZUR POSITION",
          start: "START",
          close: "SCHLIESSEN",
          cancel: "ABBRECHEN",
          cobotTimeoutNone: "COBOT TIMEOUT : keiner",
          errorIn: "FEHLER IN",
          programPaused: "Programm pausiert - CONTINUE drücken zum Fortsetzen",
          armedWaiting: "BEREIT - Wartet auf Roboter-Startsignal...",
          programRunning: "Programm läuft...",
          homingProgress: "Homing läuft...",
          notHomed: "NICHT REFERENZIERT - HOMING drücken",
          motorMoving: "Motor bewegt sich...",
          ready: "Bereit",
          mustHomeFirst: "Zuerst HOMING drücken!",
          stopMotorFirstHold: "Motor zuerst stoppen (HOLD drücken)",
          deletePosition: "Diese Position löschen?",
          invalidSteps: "Die Schrittzahl muss positiv und korrekt sein.",
          stepsTooLarge: "Die Schrittzahl ist zu groß (maximal 500.000 Schritte).",
          cannotMoveBelowZero: "Bewegung unter Null nicht möglich!",
          stopMotorFirst: "Motor zuerst stoppen (HOLD drücken)",
          systemMustBeHomed: "System muss zuerst referenziert werden!",
          noPositionsSaved: "Keine Positionen gespeichert!",
          noActivePositions: "Keine aktiven Positionen ausgewählt!",
          invalidFile: "Ungültiges Dateiformat!",
          errorReadingFile: "Fehler beim Lesen der Datei"
        },
        ro: {
          chooseLanguage: "Alege limba",
          weldingPositions: "POZIȚII DE SUDURĂ",
          weldedPieces: "PIESE SUDATE",
          positionName: "Nume poziție",
          steps: "Pași",
          status: "Stare",
          order: "Ordine",
          edit: "Editare",
          delete: "Ștergere",
          noPositions: "Nu există poziții adăugate. Mutați motorul și apăsați ADD.",
          actualPosition: "POZIȚIE ACTUALĂ (PAȘI)",
          motorSpeed: "VITEZA MOTORULUI",
          setNewHomePosition: "Setare poziție Home nouă",
          setHomeMessage: "Contorul va fi resetat și poziția fizică actuală va deveni Home (0 pași).",
          areYouSure: "Sigur doriți să continuați?",
          confirm: "CONFIRMARE",
          startProgram: "Pornire program",
          startProgramWith: "Porniți programul cu",
          activePositions: "poziții active",
          inactiveSkipped: "Pozițiile inactive vor fi omise.",
          goToPosition: "Mergi la poziție",
          selectPosition: "Selectați poziția",
          save: "SALVARE",
          load: "ÎNCĂRCARE",
          homing: "HOMING",
          goHome: "LA HOME",
          setHome: "SETARE HOME",
          goToPos: "LA POZIȚIE",
          start: "START",
          close: "ÎNCHIDE",
          cancel: "ANULARE",
          cobotTimeoutNone: "COBOT TIMEOUT : fără",
          errorIn: "EROARE ÎN",
          programPaused: "Program pauzat - apăsați CONTINUE pentru reluare",
          armedWaiting: "ARMAT - Așteaptă semnalul de start al robotului...",
          programRunning: "Program în execuție...",
          homingProgress: "Homing în curs...",
          notHomed: "FĂRĂ HOMING - apăsați HOMING",
          motorMoving: "Motorul se mișcă...",
          ready: "Gata",
          mustHomeFirst: "Apăsați mai întâi HOMING!",
          stopMotorFirstHold: "Opriți mai întâi motorul (apăsați HOLD)",
          deletePosition: "Ștergeți această poziție?",
          invalidSteps: "Numărul de pași trebuie să fie pozitiv și corect.",
          stepsTooLarge: "Numărul de pași este prea mare (maxim 500.000).",
          cannotMoveBelowZero: "Nu se poate merge sub zero!",
          stopMotorFirst: "Opriți mai întâi motorul (apăsați HOLD)",
          systemMustBeHomed: "Sistemul trebuie să aibă homing!",
          noPositionsSaved: "Nu există poziții salvate!",
          noActivePositions: "Nu există poziții active selectate!",
          invalidFile: "Format fișier invalid!",
          errorReadingFile: "Eroare la citirea fișierului"
        },
        ar: {
          chooseLanguage: "اختر اللغة",
          weldingPositions: "مواضع اللحام",
          weldedPieces: "القطع الملحومة",
          positionName: "اسم الموضع",
          steps: "الخطوات",
          status: "الحالة",
          order: "الترتيب",
          edit: "تعديل",
          delete: "حذف",
          noPositions: "لا توجد مواضع مضافة. حرّك الموتور واضغط ADD.",
          actualPosition: "الموضع الحالي (خطوات)",
          motorSpeed: "سرعة الموتور",
          setNewHomePosition: "تعيين موضع Home جديد",
          setHomeMessage: "سيتم تصفير العداد وجعل الموضع الحالي هو Home (0 خطوات).",
          areYouSure: "هل أنت متأكد من المتابعة؟",
          confirm: "تأكيد",
          startProgram: "تشغيل البرنامج",
          startProgramWith: "تشغيل البرنامج مع",
          activePositions: "مواضع فعالة",
          inactiveSkipped: "سيتم تخطي المواضع غير الفعالة.",
          goToPosition: "الذهاب إلى موضع",
          selectPosition: "اختر الموضع",
          save: "حفظ",
          load: "تحميل",
          homing: "HOMING",
          goHome: "العودة إلى HOME",
          setHome: "تعيين HOME",
          goToPos: "الذهاب إلى موضع",
          start: "START",
          close: "إغلاق",
          cancel: "إلغاء",
          cobotTimeoutNone: "مهلة الروبوت : بدون",
          errorIn: "خطأ خلال",
          programPaused: "البرنامج متوقف مؤقتًا - اضغط CONTINUE للاستمرار",
          armedWaiting: "النظام جاهز - بانتظار إشارة بدء الروبوت...",
          programRunning: "البرنامج يعمل...",
          homingProgress: "Homing قيد التنفيذ...",
          notHomed: "لم يتم Homing - اضغط HOMING",
          motorMoving: "الموتور يتحرك...",
          ready: "جاهز",
          mustHomeFirst: "يجب الضغط على HOMING أولًا!",
          stopMotorFirstHold: "أوقف الموتور أولًا (اضغط HOLD)",
          deletePosition: "هل تريد حذف هذا الموضع؟",
          invalidSteps: "عدد الخطوات يجب أن يكون موجبًا وصحيحًا.",
          stepsTooLarge: "عدد الخطوات كبير جدًا (الحد الأقصى 500,000 خطوة).",
          cannotMoveBelowZero: "لا يمكن الحركة تحت الصفر!",
          stopMotorFirst: "أوقف الموتور أولًا (اضغط HOLD)",
          systemMustBeHomed: "يجب عمل Homing للنظام أولًا!",
          noPositionsSaved: "لا توجد مواضع محفوظة!",
          noActivePositions: "لا توجد مواضع فعالة مختارة!",
          invalidFile: "صيغة الملف غير صحيحة!",
          errorReadingFile: "خطأ في قراءة الملف"
        },
        pl: {
          chooseLanguage: "Wybierz język",
          weldingPositions: "POZYCJE SPAWANIA",
          weldedPieces: "SPAWANE SZTUKI",
          positionName: "Nazwa pozycji",
          steps: "Kroki",
          status: "Status",
          order: "Kolejność",
          edit: "Edycja",
          delete: "Usuń",
          noPositions: "Nie dodano pozycji. Przesuń silnik i naciśnij ADD.",
          actualPosition: "AKTUALNA POZYCJA (KROKI)",
          motorSpeed: "PRĘDKOŚĆ SILNIKA",
          setNewHomePosition: "Ustaw nową pozycję Home",
          setHomeMessage: "Licznik zostanie wyzerowany, a aktualna pozycja fizyczna ustawiona jako Home (0 kroków).",
          areYouSure: "Czy na pewno chcesz kontynuować?",
          confirm: "POTWIERDŹ",
          startProgram: "Uruchom program",
          startProgramWith: "Uruchomić program z",
          activePositions: "aktywnymi pozycjami",
          inactiveSkipped: "Nieaktywne pozycje zostaną pominięte.",
          goToPosition: "Przejdź do pozycji",
          selectPosition: "Wybierz pozycję",
          save: "ZAPISZ",
          load: "WCZYTAJ",
          homing: "HOMING",
          goHome: "DO HOME",
          setHome: "USTAW HOME",
          goToPos: "DO POZYCJI",
          start: "START",
          close: "ZAMKNIJ",
          cancel: "ANULUJ",
          cobotTimeoutNone: "COBOT TIMEOUT : brak",
          errorIn: "BŁĄD ZA",
          programPaused: "Program wstrzymany - naciśnij CONTINUE, aby wznowić",
          armedWaiting: "UZBROJONY - oczekiwanie na sygnał startu robota...",
          programRunning: "Program działa...",
          homingProgress: "Homing w toku...",
          notHomed: "BRAK HOMING - naciśnij HOMING",
          motorMoving: "Silnik się porusza...",
          ready: "Gotowy",
          mustHomeFirst: "Najpierw naciśnij HOMING!",
          stopMotorFirstHold: "Najpierw zatrzymaj silnik (naciśnij HOLD)",
          deletePosition: "Usunąć tę pozycję?",
          invalidSteps: "Liczba kroków musi być dodatnia i poprawna.",
          stepsTooLarge: "Liczba kroków jest za duża (maks. 500 000).",
          cannotMoveBelowZero: "Nie można zejść poniżej zera!",
          stopMotorFirst: "Najpierw zatrzymaj silnik (naciśnij HOLD)",
          systemMustBeHomed: "System musi najpierw wykonać homing!",
          noPositionsSaved: "Brak zapisanych pozycji!",
          noActivePositions: "Nie wybrano aktywnych pozycji!",
          invalidFile: "Nieprawidłowy format pliku!",
          errorReadingFile: "Błąd odczytu pliku"
        }
      },
      currentSteps: 0,
      positions: [],
      nextId: 1,
      isHomed: false,
      isMoving: false,
      isHoming: false,
      isProgramRunning: false,
      isProgramPaused: false,
      // isArmed: true = Arduino is in ARMED state waiting for robot signal.
      // Only the START button is disabled by isArmed.
      // ALL other buttons (CW/CCW/HOLD/ADD/DELETE/EDIT/ORDER/SAVE/LOAD) work normally.
      isArmed: false,
      activePositionIndex: -1,
      motorSpeed: 100,
      lastSpeedSent: 100,
      showHomeDialog: false,
      showStartDialog: false,
      pendingStartStepList: "",
      pendingStartPositionCount: 0,
      showGoToPosDialog: false,
      selectedGoToPositionId: null,
      weldedPieces: 0,
      cobotTimeoutSetting: 900,
      cobotSecondsLeft: null,
      isWaitingCobot: false,
      cobotTimeoutOptions: [
        { label: "5 min", value: 300 },
        { label: "15 min", value: 900 },
        { label: "30 min", value: 1800 },
        { label: "60 min", value: 3600 },
        { label: "none", value: 0 }
      ]
    }
  },

  computed: {
    currentLanguageFlagClass() {
      const language = this.languageOptions.find(item => item.code === this.selectedLanguage);
      return language ? language.flagClass : "flag-en";
    },

    canGoToPos() {
      return this.isHomed &&
             this.positions.length > 0 &&
             !this.isArmed &&
             !this.isMoving &&
             !this.isHoming &&
             (!this.isProgramRunning || this.isProgramPaused);
    },

    goToPositionItems() {
      return [
        { id: null, label: "---------", steps: null },
        ...this.positions.map((pos, index) => ({
          id: pos.id,
          label: "POS " + (index + 1),
          steps: pos.steps
        }))
      ];
    },

    cobotTimeoutDisplay() {
      if (this.cobotTimeoutSetting === 0) return this.tr("cobotTimeoutNone");
      if (this.isWaitingCobot && this.cobotSecondsLeft !== null) {
        return this.tr("errorIn") + " : " + this.cobotSecondsLeft + "s";
      }
      return this.tr("errorIn") + " : " + this.cobotTimeoutSetting + "s";
    },

    cobotTimeoutChipColor() {
      if (this.cobotTimeoutSetting === 0) return "grey";
      if (this.isWaitingCobot) return "orange";
      return "primary";
    },

    statusText() {
      if (this.isProgramPaused)  return this.tr("programPaused");
      if (this.isArmed)          return this.tr("armedWaiting");
      if (this.isProgramRunning) return this.tr("programRunning");
      if (this.isHoming)         return this.tr("homingProgress");
      if (!this.isHomed)         return this.tr("notHomed");
      if (this.isMoving)         return this.tr("motorMoving");
      return this.tr("ready");
    },

    statusColor() {
      if (this.isProgramPaused)  return "amber";
      if (this.isArmed)          return "purple";
      if (this.isProgramRunning) return "blue";
      if (!this.isHomed)         return "red";
      if (this.isMoving || this.isHoming) return "orange";
      return "green";
    }
  },

  mounted() {
    const savedLanguage = localStorage.getItem("welding_dashboard_language");
    if (savedLanguage && this.languageOptions.some(lang => lang.code === savedLanguage)) {
      this.selectedLanguage = savedLanguage;
    }

    this.statusInterval = setInterval(() => {
      if (!this.isMoving && !this.isHoming && !this.isProgramRunning) {
        this.send({ payload: "STATUS" });
      }
    }, 1500);

    const saved = localStorage.getItem('welding_positions');
    if (saved) {
      try {
        this.positions = JSON.parse(saved).map(pos => ({ ...pos, active: pos.active !== false }));
        this.nextId = Math.max(...this.positions.map(p => p.id || 0), 0) + 1;
      } catch(e) {}
    }

    const savedPieces = localStorage.getItem('welding_welded_pieces');
    if (savedPieces !== null) {
      const parsedPieces = parseInt(savedPieces);
      if (!isNaN(parsedPieces)) this.weldedPieces = parsedPieces;
    }

    const savedTimeout = localStorage.getItem('welding_cobot_timeout_seconds');
    if (savedTimeout !== null) {
      const parsedTimeout = parseInt(savedTimeout);
      if (!isNaN(parsedTimeout)) this.cobotTimeoutSetting = parsedTimeout === 120 ? 900 : parsedTimeout;
    }
    this.sendCobotTimeout();
  },

  beforeDestroy() {
    if (this.statusInterval) clearInterval(this.statusInterval);
  },

  unmounted() {
    if (this.statusInterval) clearInterval(this.statusInterval);
  },

  watch: {
    selectedLanguage(newLanguage) {
      localStorage.setItem("welding_dashboard_language", newLanguage);
    },

    positions: {
      deep: true,
      handler(newPos) {
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
          if (part.startsWith('PAUSED:')) this.isProgramPaused = (part.split(':')[1] === '1');
          if (part.startsWith('POS:'))   this.currentSteps = parseInt(part.split(':')[1]);
          if (part.startsWith('STATE:')) {
            const state = parseInt(part.split(':')[1]);
            // States from Arduino: IDLE=0, HOMING=1, MANUAL_MOVING=2, ARMED=5, PROGRAM_MOVING=7, MANUAL_GO_HOME=13
            this.isArmed = (state === 5);
            this.isHoming = (state === 1);
            this.isMoving = (state === 2 || state === 3 || state === 7 || state === 11 || state === 12 || state === 13 || state === 17);
            this.isProgramPaused = this.isProgramPaused || (state === 16);

            if (this.isArmed) {
              this.isProgramRunning = false;
            }
          }
        });
        return;
      }

      // Arduino restarted
      if (text.startsWith("STATUS:MOVING_TO_POSITION_")) {
        this.activePositionIndex = this.activePositionToRowIndex(parseInt(text.substring(26)) - 1);
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
        this.isWaitingCobot = false;
        this.cobotSecondsLeft = null;
        this.sendCobotTimeout();
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
          text === "STATUS:GO_TO_POSITION_REACHED" ||
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

      if (text === "STATUS:PROGRAM_EXECUTION_STARTED" ||
          text === "STATUS:ROBOT_START_SIGNAL_RECEIVED") {
        this.isArmed = false;
        this.isProgramRunning = true;
      }

      if (text === "STATUS:PROGRAM_PAUSED") {
        this.isProgramPaused = true;
        this.isArmed = false;
        this.isProgramRunning = true;
        this.isMoving = false;
      }

      if (text === "STATUS:PROGRAM_RESUMED") {
        this.isProgramPaused = false;
        this.isProgramRunning = true;
      }
      if (text === "STATUS:CYCLE_COMPLETE_PIECE_DONE") {
        this.isProgramRunning = false;
        this.isWaitingCobot = false;
        this.cobotSecondsLeft = null;
        this.weldedPieces++;
        localStorage.setItem('welding_welded_pieces', String(this.weldedPieces));
        // isArmed will be set true by the next ARMED_WAITING message from Arduino
      }

      if (text === "STATUS:WAITING_FOR_COBOT_RESPONSE") {
        this.isWaitingCobot = true;
        this.cobotSecondsLeft = this.cobotTimeoutSetting === 0 ? null : this.cobotTimeoutSetting;
      }

      if (text.startsWith("STATUS:WAITING_FOR_COBOT_RESPONSE_SECONDS_LEFT:")) {
        this.isWaitingCobot = true;
        this.cobotSecondsLeft = parseInt(text.split(':').pop());
      }

      if (text === "STATUS:COBOT_FINISHED_WAITING_3_SECONDS" ||
          text.startsWith("STATUS:WELD_COMPLETE_POSITION_") ||
          text === "STATUS:RETURNING_TO_HOME") {
        this.isWaitingCobot = false;
        this.cobotSecondsLeft = null;
      }

      // Arduino confirmed disarm (user took action while armed)
      if (text === "STATUS:DISARMED_BY_OPERATOR" ||
          text === "STATUS:CONFIGURATION_UNLOCKED") {
        this.isArmed = false;
        this.isProgramRunning = false;
        this.isWaitingCobot = false;
        this.cobotSecondsLeft = null;
      }

      // E-STOP or error resets everything
      if (text === "STATUS:PROGRAM_STOPPED_KEEP_HOME") {
        this.isProgramRunning = false;
        this.isProgramPaused = false;
        this.isArmed = false;
        this.isMoving = false;
        this.isWaitingCobot = false;
        this.cobotSecondsLeft = null;
        this.activePositionIndex = -1;
      }

      if (text === "STATUS:SYSTEM_REQUIRES_NEW_HOMING") {
        this.isProgramRunning = false;
        this.isArmed = false;
      }

      if (text.startsWith("ERROR:")) {
        this.isHoming = false;
        this.isMoving = false;
        this.isProgramRunning = false;
        this.isArmed = false;
        this.isWaitingCobot = false;
        this.cobotSecondsLeft = null;
      }
    }
  },

  methods: {
    tr(key) {
      const selected = this.translations[this.selectedLanguage] || this.translations.en;
      return selected[key] || this.translations.en[key] || key;
    },

    resetWeldedPieces() {
      this.weldedPieces = 0;
      localStorage.setItem('welding_welded_pieces', '0');
    },

    activePositionToRowIndex(activeIndex) {
      let seenActive = -1;
      for (let index = 0; index < this.positions.length; index++) {
        if (this.positions[index].active !== false) {
          seenActive++;
          if (seenActive === activeIndex) return index;
        }
      }
      return -1;
    },

    sendCobotTimeout() {
      localStorage.setItem('welding_cobot_timeout_seconds', String(this.cobotTimeoutSetting));
      this.cobotSecondsLeft = null;
      this.send({ payload: "SET_COBOT_TIMEOUT " + this.cobotTimeoutSetting });
    },

    // ---------------------------------------------------------------
    // disarmIfArmed: Called before ANY user action.
    // If the system is currently ARMED, sends DISARM to Arduino and
    // ---------------------------------------------------------------
    disarmIfArmed() {
      if (this.isArmed) {
        this.send({ payload: "DISARM" });
        this.isArmed = false;
        this.isWaitingCobot = false;
        this.cobotSecondsLeft = null;
      }
    },

    saveCurrentPosition() {
      if (!this.isHomed)    { alert(this.tr("mustHomeFirst"));                  return; }
      if (this.isMoving)    { alert(this.tr("stopMotorFirstHold")); return; }
      if (this.isProgramRunning) { return; }

      this.disarmIfArmed();

      const newPos = {
        id: this.nextId++,
        name: "POS " + (this.positions.length + 1),
        steps: this.currentSteps,
        editing: false,
        active: true
      };
      this.positions.push(newPos);
      this.send({ payload: "ADD" });
    },

    togglePositionActive(pos) {
      if (this.isProgramRunning) return;
      pos.active = pos.active === false;
      this.disarmIfArmed();
    },

    deletePosition(index) {
      if (this.isProgramRunning) { return; }
      if (confirm(this.tr("deletePosition"))) {
        this.disarmIfArmed();
        this.positions.splice(index, 1);
      }
    },

    toggleEdit(pos) {
      if (this.isProgramRunning) { return; }
      if (pos.editing) {
        const parsedSteps = parseInt(pos.steps);
        if (isNaN(parsedSteps) || parsedSteps < 0) {
          alert(this.tr("invalidSteps"));
          return;
        }
        if (parsedSteps > 500000) {
          alert(this.tr("stepsTooLarge"));
          return;
        }
        pos.steps = parsedSteps;

        this.disarmIfArmed();
      }
      pos.editing = !pos.editing;
    },

    moveUp(index) {
      if (index === 0 || this.isProgramRunning) return;
      this.disarmIfArmed();
      const temp = this.positions[index];
      this.positions.splice(index, 1);
      this.positions.splice(index - 1, 0, temp);
    },

    moveDown(index) {
      if (index === this.positions.length - 1 || this.isProgramRunning) return;
      this.disarmIfArmed();
      const temp = this.positions[index];
      this.positions.splice(index, 1);
      this.positions.splice(index + 1, 0, temp);
    },

    moveForward() {
      if (!this.isHomed) { alert(this.tr("mustHomeFirst")); return; }
      if (this.isProgramRunning && !this.isProgramPaused) { return; }
      // If ARMED: only disarm (cancel waiting for robot), do NOT move motor.
      // Motor movement only works in normal IDLE state.
      if (this.isArmed) { this.disarmIfArmed(); return; }
      this.isMoving = true;
      this.send({ payload: "MOVE_FORWARD" });
    },

    moveBackward() {
      if (!this.isHomed) { alert(this.tr("mustHomeFirst")); return; }
      if (this.currentSteps <= 0) { alert(this.tr("cannotMoveBelowZero")); return; }
      if (this.isProgramRunning && !this.isProgramPaused) { return; }
      // If ARMED: only disarm (cancel waiting for robot), do NOT move motor.
      // Motor movement only works in normal IDLE state.
      if (this.isArmed) { this.disarmIfArmed(); return; }
      this.isMoving = true;
      this.send({ payload: "MOVE_BACKWARD" });
    },

    holdMotor() {
      if (this.isProgramRunning && !this.isProgramPaused) { return; }
      if (!this.isProgramPaused) this.disarmIfArmed();
      this.isMoving = false;
      this.send({ payload: "HOLD" });
    },

    toggleProgramPause() {
      if (!this.isArmed && !this.isProgramRunning && !this.isProgramPaused) return;
      this.send({ payload: "PAUSE_PROGRAM" });
    },

    startHoming() {
      if (this.isMoving) { alert(this.tr("stopMotorFirst")); return; }
      if (this.isProgramRunning) { return; }
      this.disarmIfArmed();
      this.resetWeldedPieces();
      this.isHoming = true;
      this.send({ payload: "HOMING" });
    },

    goHome() {
      if (!this.isHomed) { alert(this.tr("systemMustBeHomed")); return; }
      if (this.currentSteps === 0) { return; }
      if (this.isProgramRunning && !this.isProgramPaused) { return; }
      if (this.isArmed) { this.disarmIfArmed(); } // Disarm but continue to move

      this.isMoving = true;
      this.send({ payload: "GO_HOME" });
    },

    openGoToPosDialog() {
      if (!this.canGoToPos) return;
      this.selectedGoToPositionId = null;
      this.showGoToPosDialog = true;
    },

    closeGoToPosDialog() {
      this.showGoToPosDialog = false;
    },

    goToSelectedPosition() {
      const selectedPosition = this.positions.find(pos => pos.id === this.selectedGoToPositionId);
      if (!selectedPosition || !this.canGoToPos) return;
      this.showGoToPosDialog = false;
      this.isMoving = true;
      this.send({ payload: "GO_TO_POS " + selectedPosition.steps });
    },

    stopProgramKeepHome() {
      if (!this.isProgramRunning || this.isProgramPaused) return;
      this.isMoving = false;
      this.isProgramRunning = false;
      this.isProgramPaused = false;
      this.isArmed = false;
      this.isWaitingCobot = false;
      this.cobotSecondsLeft = null;
      this.activePositionIndex = -1;
      this.send({ payload: "STOP" });
    },

    setHomeHere() {
      if (this.isMoving || this.isHoming || this.isProgramRunning) return;
      this.showHomeDialog = true;
    },

    confirmSetHome() {
      this.showHomeDialog = false;
      this.resetWeldedPieces();
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
      this.send({ payload: "ESTOP" });
    },

    startProgram() {
      if (this.positions.length === 0) { alert(this.tr("noPositionsSaved")); return; }
      if (!this.isHomed)               { alert(this.tr("mustHomeFirst"));    return; }
      if (this.isArmed || this.isProgramRunning) { return; }

      const activePositions = this.positions.filter(pos => pos.active !== false);
      if (activePositions.length === 0) { alert(this.tr("noActivePositions")); return; }

      this.pendingStartStepList = activePositions.map(p => p.steps).join(" ");
      this.pendingStartPositionCount = activePositions.length;
      this.showStartDialog = true;
    },
    cancelStartProgram() {
      this.showStartDialog = false;
      this.pendingStartStepList = "";
      this.pendingStartPositionCount = 0;
    },

    confirmStartProgram() {
      if (!this.pendingStartStepList) return;
      this.showStartDialog = false;
      this.send({ payload: "START_PROGRAM " + this.pendingStartStepList });
      this.pendingStartStepList = "";
      this.pendingStartPositionCount = 0;
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
                this.disarmIfArmed();
                this.positions = data.positions.map(pos => ({ ...pos, active: pos.active !== false }));
                this.nextId = Math.max(...this.positions.map(p => p.id || 0)) + 1;
              } else { alert(this.tr("invalidFile")); }
            } catch (err) { alert(this.tr("errorReadingFile") + ": " + err.message); }
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
