//MYANMAR AEROSPACE ENGINEERING UNIVERSITY
//Department of Electrical Systems and Instrumentation 

float AdcV1=0; //ADC value for Out Vtg
float AdcV2=0; //ADC value for Input Vtg
float RAdcV2=0; // Input Vtg (for Vtg Divi)
float VI=0; // Out Vtg
float VI1=0; // Input Vtg
float pADC=0; // ADC value for Input Vtg (present)
float lADC=0; // ADC value for Input Vtg (last)
float fforD=0; //flag for Input Vtg Change
float fforDC=0; //flag for Duty Cycle Change
char bf[50]; //String for Out Vtg
char bf1[50]; //String for Out Vtg ADC
char bf2[50]; // String for Duty Ratio
char bf3[50]; //String for In Vtg ADC
char bf4[50]; //String for Out Vtg ADC
char ftosV[10]; //String for Out Vtg
char ftosVIn[10]; //String for In Vtg
char ftosADc[10]; //String for Out Vtg ADC
char ftosADc1[10]; //String for In Vtg ADC
char ftoD[10]; // String for Duty Ratio change
float VtgD=0.0; //Duty ratio
int a=70;
void setup() {  
Serial.begin(9600); //budrate for serial
pinMode(A0,INPUT); //  analog for In Vtg
pinMode(A1,INPUT); // analog for Out Vtg
DDRB |=(1<<DDB2); // Output for PWM
TCCR1A =(1<<COM1B1)|(1<<COM1A1); //Timer Config
TCCR1B =(1<<WGM13)|(1<<CS11); //Timer Config
}

void loop() {
  //AdcV=analogRead(A0);
  AdcV1 = analogRead(A1);              //Read Output Vtg
  AdcV2 = analogRead(A0);              // Read Input Vtg
  VI = (((AdcV1 / 1024) * 5));         // Change Vtg Out
  VI1 = ((((AdcV2 / 1024) * 5)) * 4);  // Change Vtg In
  RAdcV2 = (AdcV2 * 4) / 3;            //ADC for In (Vtg Div)
  pADC = RAdcV2;
  if (pADC == lADC)  // Check for Input Vtg Change
  {
    fforD = 1;
  } else {
    fforD = 0;
  }
  if (fforD == 1 && RAdcV2 >= 1000 && fforDC == 0)  //15V
  {
    VtgD = 0.38;
    fforDC = 1;  // Check for Duty Ratio Change

  }

  else if (fforD == 1 && RAdcV2 >= 955 && RAdcV2 < 1000 && fforDC == 0)  //14V 15V
  {
    VtgD = 0.40;
    fforDC = 1;
  }

  else if (fforD == 1 && RAdcV2 >= 887 && RAdcV2 < 955 && fforDC == 0)  //13V 14V
  {
    VtgD = 0.41;
    fforDC = 1;
  } else if (fforD == 1 && RAdcV2 >= 817 && RAdcV2 < 887 && fforDC == 0)  //12V 13V
  {
    VtgD = 0.42;
    fforDC = 1;
  } else if (fforD == 1 && RAdcV2 >= 748 && RAdcV2 < 817 && fforDC == 0)  //11V 12V
  {
    VtgD = 0.42;
    fforDC = 1;
  } else if (fforD == 1 && RAdcV2 >= 680 && RAdcV2 < 748 && fforDC == 0)  //10V 9V
  {
    VtgD = 0.46;
    fforDC = 1;
  } else if (fforD == 1 && RAdcV2 >= 610 && RAdcV2 < 680 && fforDC == 0)  //9 V 10V
  {
    VtgD = 0.59;
    fforDC = 1;
  }
  if (AdcV1 < 1000 && VtgD < 0.7)  //Adjust Duty Ratio
  {
    VtgD = VtgD + 0.01;
  }


dtostrf(VI,4,2,ftosV);
dtostrf(AdcV1,4,2,ftosADc);
dtostrf(RAdcV2,4,2,ftosADc1);
dtostrf(VI1,4,2,ftosVIn);
dtostrf(VtgD,4,2,ftoD);
sprintf(bf3,"Input voltage is %s",ftosVIn);
sprintf(bf,"Output voltage is %s",ftosV);
sprintf(bf1,"Output ADC value is %s",ftosADc);
sprintf(bf4,"Input ADC value is %s",ftosADc1);
sprintf(bf2,"Duty Ratio is %s",ftoD);
Serial.println(bf3);
Serial.println(bf);
//Serial.println(bf1);
//Serial.println(bf4);
//Serial.println(bf2);
lADC=pADC;
ICR1=100; //set frequency
OCR1B=100*VtgD; //set Duty ratio
//Serial.println(pADC);
//Serial.println(lADC);
//Serial.println(fforD);
}


