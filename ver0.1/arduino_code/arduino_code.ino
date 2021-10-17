#include <DS3232RTC.h>

// ニキシー管ドライバに数字を指定するpin
// A,B,C,Dと数字の対応はK155ID1のデータシート参照
const int set_num_A = 2;
const int set_num_B = 3;
const int set_num_C = 4;
const int set_num_D = 5;

const int digit_10h = 6;
const int digit_1h = 7;
const int digit_10m = 8;
const int digit_1m = 9;
const int digit_10s設定 = 10;
const int digit_1s = 11;

void setup(){
    // set initial time
    // setTime(23, 31, 30, 13, 2, 2009);   //set the system time to 23h31m30s on 13Feb2009
    setTime(0, 25, 5, 18, 10, 2021);
    RTC.set(now());                     //set the RTC from the system time
    setSyncProvider(RTC.get);   // the function to get the time from the RTC

    // set output pin
    // select blink number
    pinMode(set_num_A, OUTPUT);
    pinMode(set_num_B, OUTPUT);
    pinMode(set_num_C, OUTPUT);
    pinMode(set_num_D, OUTPUT);

    // select digit to blink
    pinMode(digit_10h, OUTPUT);
    pinMode(digit_1h, OUTPUT);
    pinMode(digit_10m, OUTPUT);
    pinMode(digit_1m, OUTPUT);
    pinMode(digit_10s, OUTPUT);
    pinMode(digit_1s, OUTPUT);
}

void loop(){
    int cu_time_h = hour();
    int cu_time_m = minute();
    int cu_time_s = second();

    blink_num_to_pin(6, cu_time_h / 10);
    delayMicroseconds(1000);
    reset(digit_10h);
    delayMicroseconds(1000);
    blink_num_to_pin(5, cu_time_h % 10);
    delayMicroseconds(1000);
    reset(digit_1h);
    delayMicroseconds(1000);
    blink_num_to_pin(4, cu_time_m / 10);
    delayMicroseconds(1000);
    reset(digit_10m);
    delayMicroseconds(1000);
    blink_num_to_pin(3, cu_time_m % 10);
    delayMicroseconds(1000);
    reset(digit_1m);
    delayMicroseconds(1000);
    blink_num_to_pin(2, cu_time_s / 10);
    delayMicroseconds(1000);
    reset(digit_10s);
    delayMicroseconds(1000);
    blink_num_to_pin(1, cu_time_s % 10);
    delayMicroseconds(1000);
    reset(digit_1s);
    delayMicroseconds(1000);
}

void blink_num_to_pin(int tar_digit, int num){
    // tar_digitから対象の桁を各桁と繋がってるpinから指定
    if(tar_digit == 6){
        digitalWrite(digit_10h, HIGH);
    }else if(tar_digit == 5){
        digitalWrite(digit_1h, HIGH);
    }else if(tar_digit == 4){
        digitalWrite(digit_10m, HIGH);
    }else if(tar_digit == 3){
        digitalWrite(digit_1m, HIGH);
    }else if(tar_digit == 2){
        digitalWrite(digit_10s, HIGH);
    }else if(tar_digit == 1){
        digitalWrite(digit_1s, HIGH);
    }
    
    // numから光らせる数字を4つのpinを使って指定
    if(num == 0){
        // 0b0000
        digitalWrite(set_num_A, LOW);
        digitalWrite(set_num_B, LOW);
        digitalWrite(set_num_C, LOW);
        digitalWrite(set_num_D, LOW);
    }else if(num == 1){
        // 0b1000
        digitalWrite(set_num_A, HIGH);
        digitalWrite(set_num_B, LOW);
        digitalWrite(set_num_C, LOW);
        digitalWrite(set_num_D, LOW);
    }else if(num == 2){
        // 0b0100
        digitalWrite(set_num_A, LOW);
        digitalWrite(set_num_B, HIGH);
        digitalWrite(set_num_C, LOW);
        digitalWrite(set_num_D, LOW);
    }else if(num == 3){
        // 0b1100
        digitalWrite(set_num_A, HIGH);
        digitalWrite(set_num_B, HIGH);
        digitalWrite(set_num_C, LOW);
        digitalWrite(set_num_D, LOW);
    }else if(num == 4){
        // 0b0010
        digitalWrite(set_num_A, LOW);
        digitalWrite(set_num_B, LOW);
        digitalWrite(set_num_C, HIGH);
        digitalWrite(set_num_D, LOW);
    }else if(num == 5){
        // 0b1010
        digitalWrite(set_num_A, HIGH);
        digitalWrite(set_num_B, LOW);
        digitalWrite(set_num_C, HIGH);
        digitalWrite(set_num_D, LOW);
    }else if(num == 6){
        // 0b0110
        digitalWrite(set_num_A, LOW);
        digitalWrite(set_num_B, HIGH);
        digitalWrite(set_num_C, HIGH);
        digitalWrite(set_num_D, LOW);
    }else if(num == 7){
        // 0b1110
        digitalWrite(set_num_A, HIGH);
        digitalWrite(set_num_B, HIGH);
        digitalWrite(set_num_C, HIGH);
        digitalWrite(set_num_D, LOW);
    }else if(num == 8){
        // 0b0001
        digitalWrite(set_num_A, LOW);
        digitalWrite(set_num_B, LOW);
        digitalWrite(set_num_C, LOW);
        digitalWrite(set_num_D, HIGH);
    }else if(num == 9){
        // 0b1001
        digitalWrite(set_num_A, HIGH);
        digitalWrite(set_num_B, LOW);
        digitalWrite(set_num_C, LOW);
        digitalWrite(set_num_D, HIGH);
    }
}

void reset(int tar_pin){
    digitalWrite(tar_pin, LOW);
}
