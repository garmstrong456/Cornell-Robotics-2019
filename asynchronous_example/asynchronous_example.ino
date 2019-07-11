
uint32_t task1LastCall = 0, task2LastCall = 0;
int task1Time = 500, task2Time = 300;

void setup() {

}

void loop() {
  if (millis() > task1Time + task1LastCall) {
    task1LastCall = millis();
    doTask1();
  }

  if (millis() > task2Time + task2LastCall) {
    task2LastCall = millis();
    doTask2();
  }

}

void doTask1() {
  //do task 1
}

void doTask2() {
  //do task 2
}
