/*
  SensorDriver.h - Library for read sensor.
  Created by Paolo Patruno , November 30, 2013.
  Released into the GPL licenze.
*/

#ifndef SensorDriver_h
#define SensorDriver_h
#include "SensorDriver_config.h"
#include "Arduino.h"

#if defined(USEAJSON)
#include "aJSON.h"
#endif

#if defined (RADIORF24)
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#if defined (AES)
#include <AESLib.h>
#endif
#endif

// initialize the I2C interface
//void SensorDriverInit();

class SensorDriver
{
  public:
  virtual int setup(const char* driver, const int address, const int node=0, const char* type=NULL
#if defined (RADIORF24)
		    , char* mainbuf=0, size_t lenbuf=0, RF24Network* network=NULL
#if defined (AES)
		    , uint8_t* key=NULL , uint8_t* iv=NULL
#endif
#endif
);
    //virtual int mgroneshot(unsigned long timing);
    virtual int prepare(unsigned long& waittime) = 0;
    virtual int get(long values[],size_t lenvalues) = 0;
#if defined(USEAJSON)
   virtual aJsonObject* getJson() = 0;
#endif
    virtual ~SensorDriver();
    // Factory method
    //   SensorDriver* sd = SensorDriver::create("I2C","TMP");
    //   sd->setup(34);
    static SensorDriver* create(const char* driver,const char* type);
  protected:
    int _node;
    const char* _driver;
    const char* _type;
    int _address;
    unsigned long _timing;

#if defined (RADIORF24)
    char* _mainbuf;
    size_t _lenbuf;
    RF24Network* _network;
    #if defined (AES)
      uint8_t* _key;
      uint8_t* _iv;
      void aes_enc(char* mainbuf, size_t* buflen);
      void aes_dec(char* mainbuf, size_t* buflen);
    #endif
    uint8_t _jsrpcid;
#endif
};

#if defined (TMPDRIVER)
class SensorDriverTmp : public SensorDriver
{
  public:
  virtual int setup(const char* driver, const int address, const int node=0, const char* type=NULL
             #if defined (RADIORF24)
		    , char* mainbuf=0, size_t lenbuf=0, RF24Network* network=NULL
               #if defined (AES)
		    , uint8_t* key=NULL , uint8_t* iv=NULL
               #endif
             #endif
);
    virtual int prepare(unsigned long& waittime);
    virtual int get(long values[],size_t lenvalues);
    #if defined(USEAJSON)
    virtual aJsonObject* getJson();
    #endif
};
#endif

#if defined (ADTDRIVER)
 class SensorDriverAdt7420 : public SensorDriver
 {
 public:
   virtual int setup(const char* driver, const int address, const int node, const char* type
   #if defined (RADIORF24)
		     , char* mainbuf, size_t lenbuf, RF24Network* network
     #if defined (AES)
		     , uint8_t key[] , uint8_t iv[]
     #endif
   #endif
		     );

    virtual int prepare(unsigned long& waittime);
    virtual int get(long values[],size_t lenvalues);
  #if defined(USEAJSON)
    virtual aJsonObject* getJson();
  #endif
		     };
#endif

#if defined (RADIORF24)
 class SensorDriverRF24 : public SensorDriver
 {
 public:
   virtual int setup(const char* driver, const int address, const int node, const char* type, char* mainbuf, size_t lenbuf, RF24Network* network
  #if defined (AES)
			, uint8_t key[] , uint8_t iv[]
  #endif
);
    virtual int prepare(unsigned long& waittime);
    virtual int get(long values[],size_t lenvalues);
  #if defined(USEAJSON)
    virtual aJsonObject* getJson();
  #endif
};
#endif


#if defined (HIHDRIVER)
 class SensorDriverHih6100 : public SensorDriver
 {
 public:
   virtual int setup(const char* driver, const int address, const int node, const char* type
  #if defined (RADIORF24)
		     , char* mainbuf, size_t lenbuf, RF24Network* network
    #if defined (AES)
		     , uint8_t key[] , uint8_t iv[]
    #endif
  #endif
		     );
    virtual int prepare(unsigned long& waittime);
    virtual int get(long values[],size_t lenvalues);
  #if defined(USEAJSON)
    virtual aJsonObject* getJson();
  #endif
};
#endif

#if defined (HYTDRIVER)
#include "hyt271.h"
 class SensorDriverHyt271 : public SensorDriver
 {
 public:
   virtual int setup(const char* driver, const int address, const int node, const char* type
  #if defined (RADIORF24)
		     , char* mainbuf, size_t lenbuf, RF24Network* network
    #if defined (AES)
		     , uint8_t key[] , uint8_t iv[]
    #endif
  #endif
		     );
    virtual int prepare(unsigned long& waittime);
    virtual int get(long values[],size_t lenvalues);
  #if defined(USEAJSON)
    virtual aJsonObject* getJson();
  #endif
};
#endif

#if defined (BMPDRIVER)

#define BMP085_ULTRALOWPOWER 0
#define BMP085_STANDARD      1
#define BMP085_HIGHRES       2
#define BMP085_ULTRAHIGHRES  3
#define BMP085_CAL_AC1           0xAA  // R   Calibration data (16 bits)
#define BMP085_CAL_AC2           0xAC  // R   Calibration data (16 bits)
#define BMP085_CAL_AC3           0xAE  // R   Calibration data (16 bits)    
#define BMP085_CAL_AC4           0xB0  // R   Calibration data (16 bits)
#define BMP085_CAL_AC5           0xB2  // R   Calibration data (16 bits)
#define BMP085_CAL_AC6           0xB4  // R   Calibration data (16 bits)
#define BMP085_CAL_B1            0xB6  // R   Calibration data (16 bits)
#define BMP085_CAL_B2            0xB8  // R   Calibration data (16 bits)
#define BMP085_CAL_MB            0xBA  // R   Calibration data (16 bits)
#define BMP085_CAL_MC            0xBC  // R   Calibration data (16 bits)
#define BMP085_CAL_MD            0xBE  // R   Calibration data (16 bits)

#define BMP085_CONTROL           0xF4 
#define BMP085_TEMPDATA          0xF6
#define BMP085_PRESSUREDATA      0xF6
#define BMP085_READTEMPCMD          0x2E
#define BMP085_READPRESSURECMD            0x34

 class SensorDriverBmp085 : public SensorDriver
 {
 public:
   virtual int setup(const char* driver, const int address, const int node, const char* type
  #if defined (RADIORF24)
		     , char* mainbuf, size_t lenbuf, RF24Network* network
    #if defined (AES)
		     , uint8_t key[] , uint8_t iv[]
    #endif
  #endif
		     );
    virtual int prepare(unsigned long& waittime);
    virtual int get(long values[],size_t lenvalues);
  #if defined(USEAJSON)
    virtual aJsonObject* getJson();
  #endif

  float readTemperature(void);
  int32_t readPressure(void);
  int32_t readSealevelPressure(float altitude_meters = 0);
  float readAltitude(float sealevelPressure = 101325); // std atmosphere
  uint16_t readRawTemperature(void);
  uint32_t readRawPressure(void);
  
 private:
  int32_t computeB5(int32_t UT);
  uint8_t read8(uint8_t addr);
  uint16_t read16(uint8_t addr);
  void write8(uint8_t addr, uint8_t data);

  uint8_t oversampling;

  int16_t ac1, ac2, ac3, b1, b2, mb, mc, md;
  uint16_t ac4, ac5, ac6;
};

#endif


#if defined (DAVISWIND1)
#include "registers-wind.h"

 class SensorDriverDw1 : public SensorDriver
 {
 public:
   virtual int setup(const char* driver, const int address, const int node, const char* type
  #if defined (RADIORF24)
		     , char* mainbuf, size_t lenbuf, RF24Network* network
    #if defined (AES)
		     , uint8_t key[] , uint8_t iv[]
    #endif
  #endif
     );
    virtual int prepare(unsigned long& waittime);
    virtual int get(long values[],size_t lenvalues);
  #if defined(USEAJSON)
    virtual aJsonObject* getJson();
  #endif
};
#endif


#if defined (TIPPINGBUCKETRAINGAUGE)
#include "registers-rain.h"

 class SensorDriverTbr : public SensorDriver
 {
 public:
   virtual int setup(const char* driver, const int address, const int node, const char* type
  #if defined (RADIORF24)
		     , char* mainbuf, size_t lenbuf, RF24Network* network
    #if defined (AES)
		     , uint8_t key[] , uint8_t iv[]
    #endif
  #endif
		     );
    virtual int prepare(unsigned long& waittime);
    virtual int get(long values[],size_t lenvalues);
  #if defined(USEAJSON)
    virtual aJsonObject* getJson();
  #endif
};
#endif


#if defined (TEMPERATUREHUMIDITY_ONESHOT)
#include "registers-th.h"

 class SensorDriverTHoneshot : public SensorDriver
 {
 public:
   virtual int setup(const char* driver, const int address, const int node, const char* type
  #if defined (RADIORF24)
		     , char* mainbuf, size_t lenbuf, RF24Network* network
    #if defined (AES)
		     , uint8_t key[] , uint8_t iv[]
    #endif
  #endif
		     );
    virtual int prepare(unsigned long& waittime);
    virtual int get(long values[],size_t lenvalues);
  #if defined(USEAJSON)
    virtual aJsonObject* getJson();
  #endif
};
#endif


#if defined (TEMPERATUREHUMIDITY_REPORT)
#include "registers-th.h"

 class SensorDriverTH60mean : public SensorDriver
 {
 public:
   virtual int setup(const char* driver, const int address, const int node, const char* type
  #if defined (RADIORF24)
		     , char* mainbuf, size_t lenbuf, RF24Network* network
    #if defined (AES)
		     , uint8_t key[] , uint8_t iv[]
    #endif
  #endif
		     );
    virtual int prepare(unsigned long& waittime);
    virtual int get(long values[],size_t lenvalues);
  #if defined(USEAJSON)
    virtual aJsonObject* getJson();
  #endif
};


 class SensorDriverTHmean : public SensorDriver
 {
 public:
   virtual int setup(const char* driver, const int address, const int node, const char* type
  #if defined (RADIORF24)
		     , char* mainbuf, size_t lenbuf, RF24Network* network
    #if defined (AES)
		     , uint8_t key[] , uint8_t iv[]
    #endif
  #endif
		     );
    virtual int prepare(unsigned long& waittime);
    virtual int get(long values[],size_t lenvalues);
  #if defined(USEAJSON)
    virtual aJsonObject* getJson();
  #endif
};


 class SensorDriverTHmin : public SensorDriver
 {
 public:
   virtual int setup(const char* driver, const int address, const int node, const char* type
  #if defined (RADIORF24)
		     , char* mainbuf, size_t lenbuf, RF24Network* network
    #if defined (AES)
		     , uint8_t key[] , uint8_t iv[]
    #endif
  #endif
		     );
    virtual int prepare(unsigned long& waittime);
    virtual int get(long values[],size_t lenvalues);
  #if defined(USEAJSON)
    virtual aJsonObject* getJson();
  #endif
};

 class SensorDriverTHmax : public SensorDriver
 {
 public:
   virtual int setup(const char* driver, const int address, const int node, const char* type
  #if defined (RADIORF24)
		     , char* mainbuf, size_t lenbuf, RF24Network* network
    #if defined (AES)
		     , uint8_t key[] , uint8_t iv[]
    #endif
  #endif
		     );
    virtual int prepare(unsigned long& waittime);
    virtual int get(long values[],size_t lenvalues);
  #if defined(USEAJSON)
    virtual aJsonObject* getJson();
  #endif
};

#endif


#if defined (SDS011_ONESHOT)
#include "registers-sds011.h"

 class SensorDriverSDS011oneshot : public SensorDriver
 {
 public:
   virtual int setup(const char* driver, const int address, const int node, const char* type
  #if defined (RADIORF24)
		     , char* mainbuf, size_t lenbuf, RF24Network* network
    #if defined (AES)
		     , uint8_t key[] , uint8_t iv[]
    #endif
  #endif
		     );
    virtual int prepare(unsigned long& waittime);
    virtual int get(long values[],size_t lenvalues);
  #if defined(USEAJSON)
    virtual aJsonObject* getJson();
  #endif
};
#endif


#if defined (SDS011_REPORT)
#include "registers-sds011.h"

 class SensorDriverSDS01160mean : public SensorDriver
 {
 public:
   virtual int setup(const char* driver, const int address, const int node, const char* type
  #if defined (RADIORF24)
		     , char* mainbuf, size_t lenbuf, RF24Network* network
    #if defined (AES)
		     , uint8_t key[] , uint8_t iv[]
    #endif
  #endif
		     );
    virtual int prepare(unsigned long& waittime);
    virtual int get(long values[],size_t lenvalues);
  #if defined(USEAJSON)
    virtual aJsonObject* getJson();
  #endif
};


 class SensorDriverSDS011mean : public SensorDriver
 {
 public:
   virtual int setup(const char* driver, const int address, const int node, const char* type
  #if defined (RADIORF24)
		     , char* mainbuf, size_t lenbuf, RF24Network* network
    #if defined (AES)
		     , uint8_t key[] , uint8_t iv[]
    #endif
  #endif
		     );
    virtual int prepare(unsigned long& waittime);
    virtual int get(long values[],size_t lenvalues);
  #if defined(USEAJSON)
    virtual aJsonObject* getJson();
  #endif
};


 class SensorDriverSDS011min : public SensorDriver
 {
 public:
   virtual int setup(const char* driver, const int address, const int node, const char* type
  #if defined (RADIORF24)
		     , char* mainbuf, size_t lenbuf, RF24Network* network
    #if defined (AES)
		     , uint8_t key[] , uint8_t iv[]
    #endif
  #endif
		     );
    virtual int prepare(unsigned long& waittime);
    virtual int get(long values[],size_t lenvalues);
  #if defined(USEAJSON)
    virtual aJsonObject* getJson();
  #endif
};

 class SensorDriverSDS011max : public SensorDriver
 {
 public:
   virtual int setup(const char* driver, const int address, const int node, const char* type
  #if defined (RADIORF24)
		     , char* mainbuf, size_t lenbuf, RF24Network* network
    #if defined (AES)
		     , uint8_t key[] , uint8_t iv[]
    #endif
  #endif
		     );
    virtual int prepare(unsigned long& waittime);
    virtual int get(long values[],size_t lenvalues);
  #if defined(USEAJSON)
    virtual aJsonObject* getJson();
  #endif
};

#endif


#define SD_INTERNAL_ERROR 0
#define SD_SUCCESS 1

#endif

