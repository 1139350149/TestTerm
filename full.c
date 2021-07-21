{
    unsigned char cTemp=1;
//  unsigned char cInFallErrorCount;

//  static unsigned char cInitWaterLevel;//初始水位

    if(!bGoing)
    {
        bGoing=1;
        iTimer100msSub=0x0000;
        iTimer1secEnd=iTimer1secStep-cFmInFallTime1S;
        MotorInitial();
        iFactWaterLevelFrebak=0x0000;
        bInFallOvertime=0;
//      cInFallErrorCount=0x00;
    }
    else
    {
        cLoadOutReg.allBit=0x00;
        if(hFactWaterLevel<cFmEndWaterLevel)         //到达水位
        {
            bInValveReg=1;
            if(hFactWaterLevel<=WATERLEVEL_RES)//空桶
            {
                if(!bInFallOvertime)
                {
                    if(iTimer100msSub<=6000)//6000
                    {
                        iFactWaterLevelFrebak=iFactWaterLevelFre;
                        cInFallErrorCount=0x00;
                    }
                    else if((((iTimer100msSub-9000)-3000)<=10)&&(iTimer100msSub>=9000))
                    {
                        cInFallErrorCount++;
                        if(cInFallErrorCount<80)
                        {
//                          if((((iFactWaterLevelFrebak-iFactWaterLevelFre)<80)&&(iFactWaterLevelFrebak>iFactWaterLevelFre))||(iFactWaterLevelFrebak<iFactWaterLevelFre))
                            if((abs(iFactWaterLevelFrebak-iFactWaterLevelFre)<80)||(iFactWaterLevelFrebak<iFactWaterLevelFre))
                            {
                                bErrorInFall=1;
                                iTimer100msSub=0x0000;
                                bInFallOvertime=1;
                            }
                        }
                        else if(cInFallErrorCount<=90)
                        {
                            iFactWaterLevelFrebak=iFactWaterLevelFre;
                        }
                    }
                    else
                    {
                        cInFallErrorCount=0x00;
                    }
                }
                else
                {
                    if(iTimer100msSub<=10)
                    {
                        iFactWaterLevelFrebak=iFactWaterLevelFre;
                        cInFallErrorCount=0x00;
                    }
                    else if(((iTimer100msSub-3000)<=10)&&(iTimer100msSub>=3000))
                    {
                        cInFallErrorCount++;
                        if(cInFallErrorCount<80)
                        {
//                          if((((iFactWaterLevelFrebak-iFactWaterLevelFre)<80)&&(iFactWaterLevelFrebak>iFactWaterLevelFre))||(iFactWaterLevelFrebak<iFactWaterLevelFre))
                            if((abs(iFactWaterLevelFrebak-iFactWaterLevelFre)<80)||(iFactWaterLevelFrebak<iFactWaterLevelFre))
                            {
                                bErrorInFall=1;
                                iTimer100msSub=0x0000;
                                bInFallOvertime=1;
                            }
                        }
                        else if(cInFallErrorCount<=90)
                        {
                            iFactWaterLevelFrebak=iFactWaterLevelFre;
                        }
                    }
                    else
                    {
                        cInFallErrorCount=0x00;
                    }
                }
            }
            else//桶中有水
            {
                    if(iTimer100msSub<=10)
                    {
                        iFactWaterLevelFrebak=iFactWaterLevelFre;
                        cInFallErrorCount=0x00;
                    }
                    else if(((iTimer100msSub-3000)<=10)&&(iTimer100msSub>=3000))//3000
                    {
                        cInFallErrorCount++;
                        if(cInFallErrorCount<80)
                        {
//                          if((((iFactWaterLevelFrebak-iFactWaterLevelFre)<80)&&(iFactWaterLevelFrebak>iFactWaterLevelFre))||(iFactWaterLevelFrebak<iFactWaterLevelFre))
                            if((abs(iFactWaterLevelFrebak-iFactWaterLevelFre)<80)||(iFactWaterLevelFrebak<iFactWaterLevelFre))
                            {
                                bErrorInFall=1;
                                iTimer100msSub=0x0000;
                            }
                        }
                        else if(cInFallErrorCount<=90)
                        {
                            iFactWaterLevelFrebak=iFactWaterLevelFre;
                        }
                    }
                    else
                    {
                        cInFallErrorCount=0x00;
                    }
            }

            if(iTimer100msSub>=48000)   //进水超时80min报警 48000
            {
                bErrorInFall=1;
                iTimer100msSub=0x0000;
            }
        }
        else
        {
            bGoing=0;
            MotorInitial();
            iTimer1secStep=iTimer1secEnd;
            cTemp = 0;
            bInFallOvertime=0;
            cInFallErrorCount=0x00;
        }
    }
    return cTemp;
}