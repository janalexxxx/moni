//byte character[8]={0x18, 0x3c, 0x7e, 0xdb, 0xff, 0x24, 0x5a, 0xa5}; // A space invader
//byte character[8]={0x3c, 0x42, 0xa5, 0x81, 0xa5, 0x99, 0x42, 0x3c}; // A smile
//byte character[8]={0x0, 0x0, 0x0, 0x18, 0x18, 0x0, 0x0, 0x0};
//byte character[8]={0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};





// LED variables
byte character[8]={0x6c, 0xfe, 0xfe, 0x7c, 0x38, 0x10, 0x0, 0x0};
uint8_t rowPins[8]={ A3, 12, 2, A0, 9, 3, 8, 5 };
uint8_t colPins[8]={ 13, 7, 6, A2, 4, A1, 11, 10 };

void setupLEDMatrix() {
  for(int i=0; i<8; i++) {
    pinMode(colPins[i],OUTPUT);
    pinMode(rowPins[i],OUTPUT); 
  }
}

void setLEDMatrix(uint8_t img[]) {
  for(int row=0; row<8; row++) {
    for(int k=0; k<8; k++) digitalWrite(colPins[k],HIGH); // Cleanup cols
    digitalWrite(rowPins[row], HIGH); // prepare to write the row
    for(int col=0; col<8; col++) {
      digitalWrite(colPins[7-col], img[row] & 1 << col ? LOW : HIGH);
    }
    delay(1);
    digitalWrite(rowPins[row],LOW);
  } 
}




void setup() {
 setupLEDMatrix();
}

void loop() {
  setLEDMatrix(character);
}







