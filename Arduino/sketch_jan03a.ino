/** 1B para demultiplexar 4 bits de mayor peso y 4 bits para indicar función. El retorno de los códigos de error tiene el mismo formato **/
/** Variable definition **/

byte pdPorts[13];
byte (*pFunctions[16])(byte);
char resp;
char *req;

/** Standard Functions **/

byte initModuleOutput(byte dPort){
  pinMode(dPort,OUTPUT);
  return byte(0b00000000);
}

byte initModuleInput(byte dPort){
  pinMode(dPort,INPUT);
  return byte(0b00000000);
}

byte restartModule(byte dPort){
  pinMode(dPort,LOW);
  delay(3);
  pinMode(dPort,HIGH);
  return byte(0b00000000);
}

byte startModule(byte dPort){
  pinMode(dPort,HIGH);
  return byte(0b00000000);
}

byte stopModule(byte dPort){
  pinMode(dPort,LOW);
  return byte(0b00000000);
}

void functionDefinition()
{
  pFunctions[0] = initModuleOutput;
  pFunctions[1] = initModuleInput;
  pFunctions[2] = startModule;
  pFunctions[3] = restartModule;
  pFunctions[4] = stopModule;
  /** Add here more functions **/ 
}

void setup()
{ 
  Serial.begin(9600);
  // Initialize pdPorts //
  byte i;
  for(i=0;i<=13;i++){
    pdPorts[i] = i;
  }
  // Initialise pFunctions //
  functionDefinition();
}

byte parseCommand(char* req){
  byte* pReq;
  byte auxBits;
  pReq = (byte *)req;
  byte maskHigh = 0b11110000;
  byte maskLow  = 0b00001111;
  // h = 11010000,auxBits = 01101000 & maskHigh = 01100000, auxBits >> 4 = 00000110 = 6 Módulo
  Serial.println(*pReq);
  auxBits = *pReq & maskHigh;
  auxBits = auxBits >> 4;
  Serial.println("Los bits de mayor peso son:");
  // h = 11010000,auxBits = 01101000 & maskLow = 00001000 = 4 Función
  Serial.println(auxBits);
  auxBits = *pReq & maskLow;
  Serial.println("Los bits de menor peso son:");
  Serial.println(auxBits);
  return ((byte)(*req));
}

void loop()
{
    if(Serial.available() > 0){
        Serial.readBytesUntil(1,req,1);
        parseCommand(req);   
    }
}
