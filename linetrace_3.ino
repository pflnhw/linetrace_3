extern volatile unsigned long timer0_millis;

const int motor_A1 = 5;
const int motor_A2 = 6;
const int motor_B1 = 9;
const int motor_B2 = 10;
const int IR_R = A1;
const int IR_M = A3;
const int IR_L = A5;
const int Echopin = 11;
const int Trigpin = 3;

int IR_L_data;
int IR_M_data;
int IR_R_data;
int cnt,count;
int time1,time2;

float duration, distance;

void setup() {
  pinMode(motor_A1, OUTPUT);
  pinMode(motor_A2, OUTPUT);
  pinMode(motor_B1, OUTPUT);
  pinMode(motor_B2, OUTPUT);
  pinMode(IR_L, INPUT);
  pinMode(IR_M, INPUT);
  pinMode(IR_R, INPUT);
  pinMode(Echopin, INPUT);
  pinMode(Trigpin, OUTPUT);
  Serial.begin(9600);
  Serial.print("Start");
  time1 = millis();
  time2 = millis();
}


void loop() {
  //IR 센서 값을 읽어 출력해주는 코드
  IR_L_data = digitalRead(IR_L);
  IR_M_data = digitalRead(IR_M);
  IR_R_data = digitalRead(IR_R);

  /*Serial.print(IR_L_data);
  Serial.print("-");
  Serial.print(IR_M_data);
  Serial.print("-");
  Serial.println(IR_R_data);*/
  //초음파센서
  if(millis()-time1>1000){
    time1=millis();
    digitalWrite(Trigpin, LOW);
    delayMicroseconds(2);
    digitalWrite(Trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trigpin, LOW);

    duration = pulseIn(Echopin, HIGH);
    distance = (duration*.0343)/2;

    Serial.print("Distance: ");
    Serial.println(distance);

    if(distance<20){
      turn();
      stop();
    }
  }
  if(time1>10000){
    timer0_millis=0;
    //Serial.println("reset");
  }
  // [실습] 빈칸 채우기
  // 아래 라인 트레이서 코드가 있어요. (0이 흰색, 1이 검은색)
  // 자동차가 가야할 방향을 "  " 안에 적어주세요 (직진/정지/좌회전/우회전)
  // 예)  Serial.println("직진");
  if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 0) {
    //Serial.println("직진");
    forward();
    delay(10);
    stop();
    cnt = 0;
  }
  else if (IR_L_data == 0 and IR_M_data == 0 and IR_R_data == 1) {
    //Serial.println("우회전");
    right();
    delay(10);
    stop();
    cnt = 0;
  }
  else if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 1) {
    //Serial.println("우회전");
    right();
    delay(10);
    stop();
    cnt = 0;
  }
  else if (IR_L_data == 1 and IR_M_data == 0 and IR_R_data == 0) {
    //Serial.println("좌회전");
    left();
    delay(10);
    stop();
    cnt = 0;
  }
  else if (IR_L_data == 1 and IR_M_data == 1 and IR_R_data == 0) {
    //Serial.println("좌회전");
    left();
    delay(10);
    stop();
    cnt = 0;
  }
  else if (IR_L_data == 0 and IR_M_data == 0 and IR_R_data == 0) {
    //Serial.println("정지");
    cnt++;
    delay(10);
    if(cnt>50){
      backward();
    }
  }
}

void right () {
  //우
  digitalWrite(motor_A1, HIGH);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, LOW);
}

void left() {
  //좌
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, HIGH);
  digitalWrite(motor_B2, LOW);
}

void forward() {
  //전진
  digitalWrite(motor_A1, HIGH);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, HIGH);
  digitalWrite(motor_B2, LOW);
}

void backward() {
  //후진
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, HIGH);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, HIGH);
}

void stop() {
  //정지
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, LOW);
}

void turn(){
  //유턴
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, HIGH);
  delay(1500);
}