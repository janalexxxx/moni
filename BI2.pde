import processing.video.*;
Capture video;

int led01;int led02;int led03;int led04;int led05;int led06;int led07;int led08;int led09;int led10;int led11;int led12;int led13;int led14;
int led15;int led16;int led17;int led18;int led19;int led20;int led21;int led22;int led23;int led24;int led25;int led26;int led27;int led28;
int led29;int led30;int led31;int led32;int led33;int led34;int led35;int led36;int led37;int led38;int led39;int led40;int led41;int led42;
int led43;int led44;int led45;int led46;int led47;int led48;int led49;int led50;int led51;int led52;int led53;int led54;int led55;int led56;
int led57;int led58;int led59;int led60;int led61;int led62;int led63;int led64;

float Messwert;


void setup(){
  size(1200,600);
  background(50);
  
  video = new Capture(this, width, height);
  video.start();
}

void draw(){
  
  if (video.available()) {
    video.read();
  image(video, 600, 0, width, height);
  
  int brightestX = 0;
  int brightestY = 0;
  video.loadPixels();
  int index = 0;
  float brightestValue = 0;
  for (int y = 0; y < video.height; y++) {
      for (int x = 0; x < video.width; x++) {
         int pixelValue = video.pixels[index];
         float pixelBrightness = brightness(pixelValue);
         
          if (pixelBrightness > brightestValue) {
            brightestValue = pixelBrightness;

            brightestY = y;
            brightestX = x;
          }
      }
      index++;
  }
  //fill(255,0,0);
  //ellipse(900, brightestY, 50, 50);
  textSize(72);
  fill(255);
  text(brightestValue, 650, height/2);
  println("Brightest Value = " + brightestValue);       
  
  float mposition = map(mouseX, 0, width, 0, 250);
  text(mposition, 650, height/2+100);
  
  textSize(36);
  text("Hold key to change mode", 680, height-100);
  
  noStroke();
  
  if(keyPressed){
    Messwert = mposition;
  } else {
    Messwert = brightestValue;
  }
  
  //Mitte
  if(Messwert > 150){
    led28 = 255; 
    led29 = 255;
    led36 = 255;
    led37 = 255;
  } else {
      led28 = 0; 
      led29 = 0;
      led36 = 0;
      led37 = 0;
  }
  
  //Ring1
  if(Messwert > 160){
    led20 = 255; 
    led21 = 255;
    led27 = 255;
    led30 = 255;
    led35 = 255;
    led38 = 255;
    led44 = 255;
    led45 = 255;
  } else {
      led20 = 0; 
      led21 = 0;
      led27 = 0;
      led30 = 0;
      led35 = 0; 
      led38 = 0;
      led44 = 0;
      led45 = 0;
  }
  
  //Ring2
  if(Messwert > 170){
    led12 = 255; 
    led13 = 255;
    led26 = 255;
    led31 = 255;
    led34 = 255;
    led39 = 255;
    led52 = 255;
    led53 = 255;
  } else {
      led12 = 0; 
      led13 = 0;
      led26 = 0;
      led31 = 0;
      led34 = 0; 
      led39 = 0;
      led52 = 0;
      led53 = 0;
  }
  
  //Ring3
  if(Messwert > 180){
    led04 = 255;
    led05 = 255;
    led25 = 255;
    led32 = 255;
    led33 = 255;
    led40 = 255;
    led60 = 255;
    led61 = 255;
  } else {
      led04 = 0;
      led05 = 0;
      led25 = 0;
      led32 = 0;
      led33 = 0;
      led40 = 0;
      led60 = 0;
      led61 = 0;
  }
  
  //Ring4
  if(Messwert > 190){
    led03 = 255; 
    led06 = 255;
    led11 = 255;
    led14 = 255;
    led17 = 255;
    led18 = 255;
    led23 = 255;
    led24 = 255;
    led41 = 255;
    led42 = 255;
    led47 = 255;
    led48 = 255;
    led51 = 255;
    led54 = 255;
    led59 = 255;
    led62 = 255;
  } else {
      led03 = 0; 
      led06 = 0;
      led11 = 0;
      led14 = 0;
      led17 = 0;
      led18 = 0;
      led23 = 0;
      led24 = 0;
      led41 = 0;
      led42 = 0;
      led47 = 0;
      led48 = 0;
      led51 = 0;
      led54 = 0;
      led59 = 0;
      led62 = 0;
  }
  
  //Ring5
  if(Messwert > 200){
    led02 = 255;
    led07 = 255;
    led09 = 255;
    led16 = 255;
    led49 = 255;
    led56 = 255;
    led58 = 255;
    led63 = 255;
  } else {
      led02 = 0;
      led07 = 0;
      led09 = 0;
      led16 = 0;
      led49 = 0;
      led56 = 0;
      led58 = 0;
      led63 = 0;
  }
  
  //Diagonalen1
  if(Messwert > 230){
    led01 = 255;
    led64 = 255; 
    led08 = 255;
    led57 = 255; 
  } else {
      led01 = 0;
      led64 = 0;    
      led08 = 0;
      led57 = 0;
  }
   //Diagonalen2
   if(Messwert > 220){
    led10 = 255;
    led55 = 255;  
    led15 = 255;
    led50 = 255;  
  } else {
      led10 = 0;
      led55 = 0;
      led15 = 0;
      led50 = 0;
  }
   //Diagonalen3
   if(Messwert > 210){
    led19 = 255;
    led46 = 255;
    led22 = 255;
    led43 = 255;
  } else {
      led19 = 0;
      led46 = 0;    
      led22 = 0;
      led43 = 0;
  }
  
  //horizontale Sortierung(x):
  //Reihe1
  fill(led01);
  ellipse(37.5,37.5,50,50);
  fill(led02);
  ellipse(112.5,37.5,50,50);
  fill(led03);
  ellipse(187.5,37.5,50,50);
  fill(led04);
  ellipse(262.5,37.5,50,50);
  fill(led05);
  ellipse(337.5,37.5,50,50);
  fill(led06);
  ellipse(412.5,37.5,50,50);
  fill(led07);
  ellipse(487.5,37.5,50,50);
  fill(led08);
  ellipse(562.5,37.5,50,50);
  //Reihe2
  fill(led09);
  ellipse(37.5,112.5,50,50);
  fill(led10);
  ellipse(112.5,112.5,50,50);
  fill(led11);
  ellipse(187.5,112.5,50,50);
  fill(led12);
  ellipse(262.5,112.5,50,50);
  fill(led13);
  ellipse(337.5,112.5,50,50);
  fill(led14);
  ellipse(412.5,112.5,50,50);
  fill(led15);
  ellipse(487.5,112.5,50,50);
  fill(led16);
  ellipse(562.5,112.5,50,50);
  //Reihe3
  fill(led17);
  ellipse(37.5,187.5,50,50);
  fill(led18);
  ellipse(112.5,187.5,50,50);
  fill(led19);
  ellipse(187.5,187.5,50,50);
  fill(led20);
  ellipse(262.5,187.5,50,50);
  fill(led21);
  ellipse(337.5,187.5,50,50);
  fill(led22);
  ellipse(412.5,187.5,50,50);
  fill(led23);
  ellipse(487.5,187.5,50,50);
  fill(led24);
  ellipse(562.5,187.5,50,50);
  //Reihe4
  fill(led25);
  ellipse(37.5,262.5,50,50);
  fill(led26);
  ellipse(112.5,262.5,50,50);
  fill(led27);
  ellipse(187.5,262.5,50,50);
  fill(led28);
  ellipse(262.5,262.5,50,50);
  fill(led29);
  ellipse(337.5,262.5,50,50);
  fill(led30);
  ellipse(412.5,262.5,50,50);
  fill(led31);
  ellipse(487.5,262.5,50,50);
  fill(led32);
  ellipse(562.5,262.5,50,50);
  //Reihe5
  fill(led33);
  ellipse(37.5,337.5,50,50);
  fill(led34);
  ellipse(112.5,337.5,50,50);
  fill(led35);
  ellipse(187.5,337.5,50,50);
  fill(led36);
  ellipse(262.5,337.5,50,50);
  fill(led37);
  ellipse(337.5,337.5,50,50);
  fill(led38);
  ellipse(412.5,337.5,50,50);
  fill(led39);
  ellipse(487.5,337.5,50,50);
  fill(led40);
  ellipse(562.5,337.5,50,50);
  //Reihe6
  fill(led41);
  ellipse(37.5,412.5,50,50);
  fill(led42);
  ellipse(112.5,412.5,50,50);
  fill(led43);
  ellipse(187.5,412.5,50,50);
  fill(led44);
  ellipse(262.5,412.5,50,50);
  fill(led45);
  ellipse(337.5,412.5,50,50);
  fill(led46);
  ellipse(412.5,412.5,50,50);
  fill(led47);
  ellipse(487.5,412.5,50,50);
  fill(led48);
  ellipse(562.5,412.5,50,50);
  //Reihe7
  fill(led49);
  ellipse(37.5,487.5,50,50);
  fill(led50);
  ellipse(112.5,487.5,50,50);
  fill(led51);
  ellipse(187.5,487.5,50,50);
  fill(led52);
  ellipse(262.5,487.5,50,50);
  fill(led53);
  ellipse(337.5,487.5,50,50);
  fill(led54);
  ellipse(412.5,487.5,50,50);
  fill(led55);
  ellipse(487.5,487.5,50,50);
  fill(led56);
  ellipse(562.5,487.5,50,50);
  //Reihe8
  fill(led57);
  ellipse(37.5,562.5,50,50);
  fill(led58);
  ellipse(112.5,562.5,50,50);
  fill(led59);
  ellipse(187.5,562.5,50,50);
  fill(led60);
  ellipse(262.5,562.5,50,50);
  fill(led61);
  ellipse(337.5,562.5,50,50);
  fill(led62);
  ellipse(412.5,562.5,50,50);
  fill(led63);
  ellipse(487.5,562.5,50,50);
  fill(led64);
  ellipse(562.5,562.5,50,50); 
  }
}