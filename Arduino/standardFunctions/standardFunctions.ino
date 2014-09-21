byte initModuleOutput(byte dPort){
  pinMode(dPort,OUTPUT)
}

byte init ModuleInput(byte dPort){
  pinMode(dPort,INPUT);
}

byte restartModule(byte dPort){
  pinMode(dPort,LOW);
  delay(3);
  pinMode(dPort,HIGH);
}

byte startModule(byte dPort){
  pinMode(dPort,HIGH);
}

byte stopModule(byte dPort){
  pinMode(dPort,LOW);
}
