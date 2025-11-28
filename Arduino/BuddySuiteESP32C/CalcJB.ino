//28Nov2025
void JB_Calc::setup(){}

//float tojMl, deemsRatio, pgRatio, pgMl, vgMl, deemsMg; in AllJuiceBuddy.h
/** given total djuice, dmt ratio, and pg/vg ratio, calculate pg, vg and dmt weight */  
void JB_Calc::calculate(CurrentValuesJB & jb_values, boolean Dont_Update_DeemsMg)
  {
     float tijMl = (jb_values.getTojMl()) / ((0.95 / jb_values.deemsRatio ) + 1.0);
     jb_values.pgMl = (jb_values.pgRatio/100.0) * tijMl;
     //Serial.println(String("pmMl=") + String(jb_values.pgMl));
     jb_values.vgMl = tijMl - jb_values.pgMl;
     if(!Dont_Update_DeemsMg)
    	{
        jb_values.deemsMg =  (tijMl*1000)/jb_values.deemsRatio; 
    	} 
//Serial.println(String ("dmRat=") + String(jb_values.deemsRatio, 4) + String("tijMl") + String(tijMl,4) + String(", mg=") +  String(jb_values.deemsMg));
//printing oout 1.1 to serial monitor but 1:1.0 on LCD screeen
     
     float pgSolubilityFactor_gPerMl  = jb_values.deemsMg/(jb_values.pgMl*1000);
     jb_values.solubility = SOLUBLE;
     if (pgSolubilityFactor_gPerMl>2.0){jb_values.solubility=NOT_SOLUBLE;} //red light
     else if ((pgSolubilityFactor_gPerMl>1.2) &&  (pgSolubilityFactor_gPerMl<=2.0) && (jb_values.pgRatio<40)) {jb_values.solubility=PART_SOLUBLE;}//red/amber lights

    //tojMl=(roundf(tojMlin * 10))/10.0 ;//round to 0.1 
    jb_values.weightPg_g =  jb_values.pgMl * PG_WEIGHTG_PER_ML;
    jb_values.weightPg_g = (roundf(jb_values.weightPg_g*100))/100.0; //round off to make the total weight field be the sum of the weight fields
    
    jb_values.weightVg_g =  jb_values.vgMl * VG_WEIGHTG_PER_ML;
    jb_values.weightVg_g = (roundf(jb_values.weightVg_g*100))/100.0; //round off to make the total weight field be the sum of the weight fields
    //Serial.println(String("weightVG=") + String(jb_values.weightVg_g ,8));
    jb_values.totalWeightOfDJuice_g= (jb_values.deemsMg/1000.0) + jb_values.weightPg_g + jb_values.weightVg_g;
    //Serial.println(("DmtMg=") + String(jb_values.deemsMg));
  }

  void JB_Calc::calculateForDeemsWeight(CurrentValuesJB & jb_values)
  {
    //jb_values.tojMl = (jb_values.deemsMg *(jb_values.deemsRatio + 0.95))/1000.0;
    jb_values.setTojMl((jb_values.deemsMg *(jb_values.deemsRatio + 0.95))/1000.0);
    calculate(jb_values, true);
  }
