/***************************************
课题名称：电子药盒
邵嘉懿
自动化1802
18030140238
12MHZ
***********************************************/
#include	<reg52.h>
#include	<intrins.h>
#define uint unsigned int 
#define uchar unsigned char
sbit beep=P3^1;
uchar code disbitcode[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};				  //送位码
uchar code discode[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,
0xF8,0x80,0x90,0xBF,0x91,0xFF,0x98};	  //送段码0-9和"-,y,灭灯"
uchar  disbuf[8]={0,0,10,0,0,10,2,1};										   
uchar  disbuf1[8]={13,1,0,10,10,10,1,11};			                             
uchar  disbuf2[8]={0,0,10,0,0,10,2,1};										 
uchar  disbuf3[8]={13,1,0,10,10,10,2,11};								
uchar  disbuf4[8]={0,0,10,0,0,10,0,0};
uchar  disbuf5[8]={13,1,0,10,10,10,3,11};								
uchar  disbuf6[8]={0,0,10,0,0,10,0,0};
uchar  disbuf7[8]={13,1,0,10,10,10,4,11};
uchar  disbuf8[8]={0,0,10,0,0,10,0,0};
uchar cent,cent1,second=0,minite=0,hour=12,yao1=1,yao2=1,yao3=1,yao4=1,
s1=12,s2=12,s3=12,s4=12,
f1=0,f2=0,f3=0,f4=0,
m1=20,m2=30,m3=40,m4=50;
void delay(uint m);
void display(void);
void display2(void);
void display4(void);
void display6(void);
void display8(void);
void display1(void);
void display3(void);
void display5(void);
void display7(void);
uchar keyscan();
/*************延时程序**************/											 
void delay(uint m)		 
  {
  	while(--m);
  } 
/*************显示程序**************/
void display(void)		  //数码管12——00——00 
  {
  	uchar i;
  	for(i=0;i<8;i++)
	 {
		P0=discode[disbuf[i]];
		P2=disbitcode[i];
		delay(100);	
	}
  }
	
 void display2(void)		  //数码管显示12-00-00
  {
  	uchar i;
  	for(i=0;i<8;i++)
	 {
		P0=discode[disbuf2[i]]; 
		P2=disbitcode[i];
		delay(100);	
	}
  }
	
	void display4(void)		//数码管显示00-00-00  
  {
  	uchar i;
  	for(i=0;i<8;i++)
	 {
		P0=discode[disbuf4[i]]; 
		P2=disbitcode[i];
		delay(100);	
	}
  }
	
   void display6(void)		  //数码管显示00-00-00
  {
  	uchar i;
  	for(i=0;i<8;i++)
	 {
		P0=discode[disbuf6[i]]; 
		P2=disbitcode[i];
		delay(100);	
	}
  }
	void display8(void)		  //数码管显示00-00-00
  {
  	uchar i;
  	for(i=0;i<8;i++)
	 {
		P0=discode[disbuf8[i]]; 
		P2=disbitcode[i];
		delay(100);	
	}
  }
	
void display1(void)		  //数码管显示y1    01
  {
  	uchar i;
  	for(i=0;i<8;i++)
	 {
		P0=discode[disbuf1[i]]; 
		P2=disbitcode[i];
		delay(100);	
	}
  }


  
  void display3(void)		 //数码管显示y2  01 
  {
  	uchar i;
  	for(i=0;i<8;i++)
	 {
		P0=discode[disbuf3[i]]; 
		P2=disbitcode[i];
		delay(100);	
	}
  } 
  

  void display5(void)		  //数码管显示y3     01
  {
  	uchar i;
  	for(i=0;i<8;i++)
	 {
		P0=discode[disbuf5[i]]; 
		P2=disbitcode[i];
		delay(100);	
	}
  }
	  void display7(void)		  //数码管显示y4     04
  {
  	uchar i;
  	for(i=0;i<8;i++)
	 {
		P0=discode[disbuf7[i]]; 
		P2=disbitcode[i];
		delay(100);	
	}
  }
  
  /*************初始化程序**************/
void ini(void)				
	 {
	   	  TMOD=0x11;
		  TH0=(65536-50000)/256; 
		  TL0=(65536-50000)%256;				
		  ET0=1;
		  EA=1;
	 }

void init (void)
		{
				disbuf2[0]=m1%10;  //更新显示缓冲区
			    disbuf2[1]=m1/10;
				disbuf2[3]=f1%10;
				disbuf2[4]=f1/10;
			  	disbuf2[6]=s1%10;	
				disbuf2[7]=s1/10;
				disbuf4[0]=m2%10;  //更新显示缓冲区
			    disbuf4[1]=m2/10;
				disbuf4[3]=f2%10;
				disbuf4[4]=f2/10;
			  	disbuf4[6]=s2%10;	
				disbuf4[7]=s2/10;
				disbuf6[0]=m3%10;  //更新显示缓冲区
			    disbuf6[1]=m3/10;
				disbuf6[3]=f3%10;
				disbuf6[4]=f3/10;
			  	disbuf6[6]=s3%10;	
				disbuf6[7]=s3/10;	
			disbuf8[0]=m4%10;  //更新显示缓冲区
			    disbuf8[1]=m4/10;
				disbuf8[3]=f4%10;
				disbuf8[4]=f4/10;
			  	disbuf8[6]=s4%10;	
				disbuf8[7]=s4/10;	
			
		}
/*************中断程序**************/
void t0(void) interrupt 1 using 0     //用第0组寄存器
	 {
	 	 cent++;
		 TH0=(65536-50000)/256; 
		 TL0=(65536-50000)%256;
		 if(cent==20)
		 	{
			   cent=0;
			   second++;
			   if(second>=60)
					{
					  second=0;
					  minite++;
						   	if(minite>=60)
								{
									minite=0;
									hour++;
										if(hour>=24)
											{
												hour=0;												
											}
								}
					}
				disbuf[0]=second%10;  //更新显示缓冲区
			    disbuf[1]=second/10;
				disbuf[3]=minite%10;
				disbuf[4]=minite/10;
			  	disbuf[6]=hour%10;	
				disbuf[7]=hour/10;
				
         }
    }
	 

 
/*************键扫描程序**************/
uchar keyscan()
{
 uchar tmp;			 //列号，行号
 P1=0xff;               //发全行0扫描码
 if((P1&0xff)!=0xff)     //若有键按下
  {
   delay(1000);          // 延时去抖   
   if((P1&0xff)!=0xff)          //有键按下
       {
		tmp=(P1&0xff);
	    do{}while((P1&0xff)!=0xff);
		  tmp=~tmp;
			          
      return (tmp);			 //还回键值
	  }                        
  }															
   return (0);                                //无键按下,还回0
}

/********主程序*********/
void  main (void)
{	
	 uchar v;
	 P2=0xff;
	 P0=0x0c;//数码管显示P.
	 ini(); init ();	//初始化
     while (1)
	 {
	    v=keyscan();
		if (v==1)
		{
			while (1)
			{
				switch (v)
				{
					case 1:						 
							P2=0x00; beep=1;
							TR0=1;  
						while(v==1||v==0||v==32||v==64||v==128)		   
		          		 { TR0=1;
						   display();
						   v=keyscan();
						   if (m1==second&&f1==minite&&s1==hour)
						   		{beep=0;v=2;}
							if (m2==second&&f2==minite&&s2==hour)
						   		{beep=0;v=4;}
							if (m3==second&&f3==minite&&s3==hour)
						   		{beep=0;v=8;}
              if (m4==second&&f4==minite&&s4==hour)
						   		{beep=0;v=16;}									
						   if (v==32||v==64||v==128)
						    {	
							  	while (v==32||v==64||v==128||v==0)
							   {  TR0=0;
							 	 while (v==32)
								 { hour++; if (hour>23) hour=0;disbuf[6]=hour%10;   disbuf[7]=hour/10;display(); v=keyscan();}
								 while (v==64)
								 {minite++; if (minite>59) minite=0;disbuf[3]=minite%10;	disbuf[4]=minite/10;display(); v=keyscan();}
								 while (v==128)
								 {second++; if (second>59) second=0;disbuf[0]=second%10;  disbuf[1]=second/10;display(); v=keyscan();}
								 disbuf[0]=second%10;  //更新显示缓冲区
								 disbuf[1]=second/10;
							     disbuf[3]=minite%10;
								 disbuf[4]=minite/10;
								 disbuf[6]=hour%10;	
								 disbuf[7]=hour/10;	
								  display();
						   		  v=keyscan();  
								 }
							}
						 }
					 break;
					 case 2: 					 
							P2=0x00;
						while(v==2||v==0)		   
		          		 { 
						   a:
						   display1();
						   v=keyscan();
						   if (m1==second&&f1==minite&&s1==hour)
						   		{beep=0;}
							if (m2==second&&f2==minite&&s2==hour)
						   		{beep=0;v=4;}
							if (m3==second&&f3==minite&&s3==hour)
						   		{beep=0;v=8;}
              if (m4==second&&f4==minite&&s4==hour)
						   		{beep=0;v=16;}										
						   while (v==32||v==64||v==128)
						    {
							  while (v==64)
							   {yao1++; 
							   if (yao1>99)  
								   yao1=0; 
								   disbuf1[1]=yao1%10;	
								   disbuf1[2]=yao1/10;
								   display1();
								   v=keyscan();	 
							   }
							   while (v==128)
							   {
								   yao1--; 
								   if (yao1<1)  
								   	yao1=1; 
									disbuf1[1]=yao1%10;	
									disbuf1[2]=yao1/10;
									display1();
									v=keyscan();										 
							  }	
								 display1();
								v=keyscan();
							 }			     	
						 while(v==2)
						 	while(v==2||v==0)	   
			          		 {
							   beep=1;
							   display2();
							   v=keyscan();
						    while (v==32||v==64||v==128)
						    {
							  while (v==32)
							   {s1++; 
							   if (s1>23)  
								   s1=0; 
								   disbuf2[6]=s1%10;	
								   disbuf2[7]=s1/10;
								   display2();
								   v=keyscan();	 
							   }	
							  while (v==64)
							   {f1++; 
							   if (f1>59)  
								   f1=0; 
								   disbuf2[3]=f1%10;	
								   disbuf2[4]=f1/10;
								   display2();
								   v=keyscan();	 
							   }
							   while (v==128)
							   {
								   m1++; 
								   if (m1>59)  
								   	m1=0; 
									disbuf2[0]=m1%10;	
									disbuf2[1]=m1/10;
									display2();
									v=keyscan();										 
							  }	
								 display2();
								v=keyscan();
							 }							   	
							    while(v==2)
						   			goto a;	   
							 }						 
						 }		break;
					 case 4: 					 
							P2=0x00;
						while(v==4||v==0)		   
		          		 { 
						   b:
						   display3();
						   v=keyscan();
						   if (m1==second&&f1==minite&&s1==hour)
						   		{beep=0;v=2;}
							if (m2==second&&f2==minite&&s2==hour)
						   		{beep=0;}
							if (m3==second&&f3==minite&&s3==hour)
						   		{beep=0;v=8;}	
              if (m4==second&&f4==minite&&s4==hour)
						   		{beep=0;v=16;}										
						   while (v==32||v==64||v==128)
						    {
							  while (v==64)
							   {yao2++; 
							   if (yao2>99)  
								   yao2=0; 
								   disbuf3[1]=yao2%10;	
								   disbuf3[2]=yao2/10;
								   display3();
								   v=keyscan();	 
							   }
							   while (v==128)
							   {
								   yao2--; 
								   if (yao2<1)  
								   	yao2=1; 
									disbuf3[1]=yao2%10;	
									disbuf3[2]=yao2/10;
									display3();
									v=keyscan();										 
							  }	
								 display3();
								v=keyscan();
							 }			     	
						 while(v==4)
						 	while(v==4||v==0)	   
			          		 {
							   beep=1;
							   display4();
							   v=keyscan();
						    while (v==32||v==64||v==128)
						    {
							  while (v==32)
							   {s2++; 
							   if (s2>23)  
								   s2=0; 
								   disbuf4[6]=s2%10;	
								   disbuf4[7]=s2/10;
								   display4();
								   v=keyscan();	 
							   }	
							  while (v==64)
							   {f2++; 
							   if (f2>59)  
								   f2=0; 
								   disbuf4[3]=f2%10;	
								   disbuf4[4]=f2/10;
								   display4();
								   v=keyscan();	 
							   }
							   while (v==128)
							   {
								   m2++; 
								   if (m2>59)  
								   	m2=0; 
									disbuf4[0]=m2%10;	
									disbuf4[1]=m2/10;
									display4();
									v=keyscan();										 
							  }	
								 display4();
								v=keyscan();
							 }							   	
							    while(v==4)
						   			goto b;	
							 }						 
						 }		break;
					   case 8: 					 
							P2=0x00;
						while(v==8||v==0)		   
		          		 { 
						   c:
						   display5();
						   v=keyscan();
						   if (m1==second&&f1==minite&&s1==hour)
						   		{beep=0;v=2;}
							if (m2==second&&f2==minite&&s2==hour)
						   		{beep=0;v=4;}
							if (m3==second&&f3==minite&&s3==hour)
						   		{beep=0;}			
              if (m4==second&&f4==minite&&s4==hour)
						   		{beep=0;v=16;}										
						   while (v==32||v==64||v==128)
						    {
							  while (v==64)
							   {yao3++; 
							   if (yao3>99)  
								   yao3=0; 
								   disbuf5[1]=yao3%10;	
								   disbuf5[2]=yao3/10;
								   display5();
								   v=keyscan();	 
							   }
							   while (v==128)
							   {
								   yao3--; 
								   if (yao3<1)  
								   	yao3=1; 
									disbuf5[1]=yao3%10;	
									disbuf5[2]=yao3/10;
									display5();
									v=keyscan();										 
							  }	
								 display5();
								v=keyscan();
							 }			     	
						 while(v==8)
						 	while(v==8||v==0)	   
			          		 {	beep=1;
							   display6();
							   v=keyscan();
						    while (v==32||v==64||v==128)
						    {
							  while (v==32)
							   {s3++; 
							   if (s3>23)  
								   s3=0; 
								   disbuf6[6]=s3%10;	
								   disbuf6[7]=s3/10;
								   display6();
								   v=keyscan();	 
							   }	
							  while (v==64)
							   {f3++; 
							   if (f3>59)  
								   f3=0; 
								   disbuf6[3]=f3%10;	
								   disbuf6[4]=f3/10;
								   display6();
								   v=keyscan();	 
							   }
							   while (v==128)
							   {
								   m3++; 
								   if (m3>59)  
								   	m3=0; 
									disbuf6[0]=m3%10;	
									disbuf6[1]=m3/10;
									display6();
									v=keyscan();										 
							  }	
								 display6();
								v=keyscan();
							 }							   	
							    while(v==8)
						   			goto c;
							 }						 
						 }		break;
						  case 16: 					 
							P2=0x00;
						while(v==16||v==0)		   
		         { 
						   d:
						   display7();
						   v=keyscan();
						   if (m1==second&&f1==minite&&s1==hour)
						   		{beep=0;v=2;}
							if (m2==second&&f2==minite&&s2==hour)
						   		{beep=0;v=4;}
							if (m3==second&&f3==minite&&s3==hour)
						   		{beep=0;v=8;}	
              if (m4==second&&f4==minite&&s4==hour)
						   		{beep=0;}										
						   while (v==32||v==64||v==128)
						    {
							  while (v==64)
							   { yao4++; 
							   if (yao4>99)  
								   yao4=0; 
								   disbuf7[1]=yao4%10;	
								   disbuf7[2]=yao4/10;
								   display7();
								   v=keyscan();	 
							   }
							   while (v==128)
							   {
								   yao4--; 
								   if (yao4<1)  
								   	yao4=1; 
									disbuf7[1]=yao4%10;	
									disbuf7[2]=yao4/10;
									display7();
									v=keyscan();										 
							  }	
								 display7();
								v=keyscan();
							 }			     	
						 while(v==16)
						 	while(v==16||v==0)	   
			          		 {	beep=1;
							   display8();
							   v=keyscan();
						    while (v==32||v==64||v==128)
						    {
							  while (v==32)
							   {s4++; 
							   if (s4>23)  
								   s4=0; 
								   disbuf8[6]=s4%10;	
								   disbuf8[7]=s4/10;
								   display8();
								   v=keyscan();	 
							   }	
							  while (v==64)
							   {f4++; 
							   if (f4>59)  
								   f4=0; 
								   disbuf8[3]=f4%10;	
								   disbuf8[4]=f4/10;
								   display8();
								   v=keyscan();	 
							   }
							   while (v==128)
							   {
								   m4++; 
								   if (m4>59)  
								   	m4=0; 
									disbuf8[0]=m4%10;	
									disbuf8[1]=m4/10;
									display8();
									v=keyscan();										 
							  }	
								 display8();
								v=keyscan();
							 }							   	
							    while(v==16)
						   			goto d;
							 }						 
						 }		break;
				}
			}
		}
	 }	 
} 				 	