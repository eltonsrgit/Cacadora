#ifndef sensoresIR_H
#define sensoresIR_H

#define leftIRpin 33
#define rightIRpin 25


bool LeftDetection(){
  bool left_IR_read = digitalRead(leftIRpin);
  if (left_IR_read == 0){
    return false; // sem inimigo
  }
  else{
    return true; // com inimigo
  }
}

bool RightDetection(){
  bool right_IR_read = digitalRead(rightIRpin);
  if (right_IR_read == 0){
    return false; // sem inimigo
  }
  else{
    return true;  // com inimigo
  }
}

#endif