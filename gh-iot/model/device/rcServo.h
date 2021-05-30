#pragma once

void rcServo_init();
void rcServo_turnLeft(int servoId,int leftPercent);
void rcServo_turnRight(int servoId,int rightPercent);
void rcServo_backToZero(int servoId);