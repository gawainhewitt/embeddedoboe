void drawMenu() {
  u8g2.firstPage();
  do {
    draw();
  } while ( u8g2.nextPage() );
}

void draw() {
  if (bigMenu) {
    u8g2.setFont(u8g2_font_inr21_mr);
    u8g2.setCursor(1, 30);
    u8g2.print(keyName);
    u8g2.setCursor(1, 60);
    u8g2.print(chordTypeName);
  } else {
    u8g2.setFont(u8g2_font_6x13_tr);
    
    u8g2.setCursor(1, 10);
    u8g2.print("Key: "); 
    u8g2.print(keyName); 
    
    u8g2.setCursor(1, 20);
    

    u8g2.setCursor(1, 30);
    u8g2.print("Type: "); u8g2.print(chordTypeName);

    u8g2.setCursor(1, 40);
    

    u8g2.setCursor(1, 50);
    

    u8g2.setCursor(1, 60);
    int volumeToPrint = static_cast<int>(gain*100);
    u8g2.print("Volume: "); u8g2.print(volumeToPrint);
    
    u8g2.drawFrame(0, activeMenuInput * 20, 127, 10);
  }
}
