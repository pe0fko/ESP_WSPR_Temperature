// *********************************************
// WSPR Clock TX ESP8266.
// 01/05/2021 Fred Krom, pe0fko
//
// Board: ESP8266	- LOLIN(WeMos) D1 R1 & mini
//					- CPU freq 80MHz
//					- Set Debug port on Serial1
//          - Erease Flash: "All Flash contents"
//
// Using library ESP8266WiFi at version 1.0
// Using library DNSServer at version 1.1.1
// Using library SPI at version 1.0
// Using library Wire at version 1.0
// Using library Adafruit_GFX_Library at version 1.11.9
// Using library Adafruit_BusIO at version 1.15.0
// Using library Adafruit_SSD1306_Wemos_Mini_OLED at version 1.1.2
// Using library Etherkit_Si5351 at version 2.1.4
// Using library Etherkit_JTEncode at version 1.3.1
// Using library OneWire at version 2.3.7
// Using library DallasTemperature at version 3.9.0
// Using library ESP8266mDNS at version 1.2
// Using library ArduinoOTA at version 1.0
//

#define		VERSION		"V3.0"

#define   I2C_SDA   5
#define   I2C_SCL   4

//#define	LOC_PE0FKO
//#define	LOC_PA3EQN
//#define	LOC_PA_PE0FKO
//#define	LOC_PE0FKO_NR
#define	LOC_LA_MOTHE_40m
//#define	LOC_LA_MOTHE_30m
//#define	LOC_LA_MOTHE_20m

//#define		FEATURE_OTA
//#define		FEATURE_mDNS
//#define		FEATURE_CARRIER
//#define		FEATURE_1H_FAST_TX
//#define		FEATURE_PRINT_TIMESLOT
//#define		FEATURE_PRINT_WSPR_SIMBOLS

// WSPR Type 1:
// The standard message is <callsign> + <4 character locator> + <dBm transmit power>;
// for example “K1ABC FN20 37” is a signal from station K1ABC in Maidenhead grid cell
// “FN20”, sending 37 dBm, or about 5.0 W (legal limit for 630 m).
// Messages with a compound callsign and/or 6 digit locator use a two-transmission sequence.
// WSPR Type 2:
// The <first transmission> carries compound callsign and power level, or standard callsign,
// 4 digit locator, and power level.
// WSPR Type 3:
// The <second transmission> carries a hashed callsign, 6 digit locator, and power level.
// Add-on prefixes can be up to three alphanumeric characters; add-on suffixes can be a
// single letter or one or two digits.

// WSPR type 1: CALL, LOC4, dBm
// WSPR type 2: p/CALL/s, dBm
// WSPR type 3: <p/CALL/s>, LOC6, dBm

// Update JTEncode.cpp library at line 1000 for 1 char prefix!

#if defined LOC_PE0FKO
	#define	HAM_PREFIX      ""				// Prefix of the ham call
	#define	HAM_CALL        "PE0FKO"        // Ham radio call sign
	#define	HAM_SUFFIX      ""				// Suffix of the ham call
	#define	HAM_LOCATOR     "JO32cd"		// JO32CD 40OJ
	#define	HAM_POWER       10				// Power TX in dBm, 9dBm measure
	#define	WSPR_TX_FREQ_0	WSPR_TX_FREQ_40m	// TX freqency Si5351 OSC 0
	#define	WSPR_TX_FREQ_1	WSPR_TX_FREQ_none	// TX freqency Si5351 OSC 1
	#define	WSPR_TX_FREQ_2	WSPR_TX_FREQ_none	// TX freqency Si5351 OSC 2
#elif defined LOC_PA3EQN
	#define	HAM_PREFIX      ""				// Prefix of the ham call
	#define	HAM_CALL        "PA3EQN"        // Ham radio call sign
	#define	HAM_SUFFIX      ""				// Suffix of the ham call
	#define	HAM_LOCATOR     "JO32cc"		// JO32CC
	#define	HAM_POWER       10				// Power TX in dBm, 9dBm measure
	#define	WSPR_TX_FREQ_0	WSPR_TX_FREQ_40m
	#define	WSPR_TX_FREQ_1	WSPR_TX_FREQ_none
	#define	WSPR_TX_FREQ_2	WSPR_TX_FREQ_none
#elif defined LOC_PA_PE0FKO
	#define	HAM_PREFIX      "PA/"			// Prefix of the ham call
	#define	HAM_CALL        "PE0FKO"		// Ham radio call sign
	#define	HAM_SUFFIX      ""				// Suffix of the ham call
	#define	HAM_LOCATOR     "JO32cd"		// JO32CD 40OJ
	#define	HAM_POWER       10				// Power TX in dBm
	#define	WSPR_TX_FREQ_0	WSPR_TX_FREQ_40m
	#define	WSPR_TX_FREQ_1	WSPR_TX_FREQ_none
	#define	WSPR_TX_FREQ_2	WSPR_TX_FREQ_none
#elif defined LOC_LA_MOTHE_40m
	#define	HAM_PREFIX      "F/"			// Prefix of the ham call
	#define	HAM_CALL        "PE0FKO"		// Ham radio call sign
	#define	HAM_SUFFIX      ""				// Suffix of the ham call
	#define	HAM_LOCATOR     "JN13IW"		// JN13IW 08UG
	#define	HAM_POWER       10				// Power TX in dBm
	#define	WSPR_TX_FREQ_0	WSPR_TX_FREQ_40m
	#define	WSPR_TX_FREQ_1	WSPR_TX_FREQ_none
	#define	WSPR_TX_FREQ_2	WSPR_TX_FREQ_none
#elif defined LOC_LA_MOTHE_30m
	#define	HAM_PREFIX      "F/"			// Prefix of the ham call
	#define	HAM_CALL        "PE0FKO"		// Ham radio call sign
	#define	HAM_SUFFIX      ""				// Suffix of the ham call
	#define	HAM_LOCATOR     "JN13IW"		// JN13IW 08UG
	#define	HAM_POWER       5				// Power TX in dBm
	#define	WSPR_TX_FREQ_0	WSPR_TX_FREQ_40m
	#define	WSPR_TX_FREQ_1	WSPR_TX_FREQ_none
	#define	WSPR_TX_FREQ_2	WSPR_TX_FREQ_none
#elif defined LOC_LA_MOTHE_20m
	#define	HAM_PREFIX      "F/"			// Prefix of the ham call
	#define	HAM_CALL        "PE0FKO"		// Ham radio call sign
	#define	HAM_SUFFIX      ""				// Suffix of the ham call
	#define	HAM_LOCATOR     "JN13IW"		// JN13IW 08UG
	#define	HAM_POWER       4				// Power TX in dBm
	#define	WSPR_TX_FREQ_0	WSPR_TX_FREQ_40m
	#define	WSPR_TX_FREQ_1	WSPR_TX_FREQ_none
	#define	WSPR_TX_FREQ_2	WSPR_TX_FREQ_none
#else
  #error    "Specify the Location..."
#endif

#define	WSPR_TX_FREQ_160m		1838000UL	// 160m  1.838000 -  1.838200
#define	WSPR_TX_FREQ_80m		3570000UL	// 80m   3.570000 -  3.570200
#define	WSPR_TX_FREQ_60m		5288600UL	// 60m   5.288600 -  5.288800
#define	WSPR_TX_FREQ_40m		7040000UL	// 40m   7.040000 -  7.040200
#define	WSPR_TX_FREQ_30m		10140100UL	// 30m  10.140100 - 10.140300
#define	WSPR_TX_FREQ_20m		14097000UL	// 20m  14.097000 - 14.097200
#define	WSPR_TX_FREQ_17m		18106000UL	// 17m  18.106000 - 18.106200
#define	WSPR_TX_FREQ_15m		21096000UL	// 15m  21.096000 - 21.096200
#define	WSPR_TX_FREQ_12m		24926000UL	// 12m  24.926000 - 24.926200
#define	WSPR_TX_FREQ_10m		28126000UL	// 10m  28.126000 - 28.126200
#define	WSPR_TX_FREQ_6m			50294400UL	// 6m   50.294400 - 50.294600
#define	WSPR_TX_FREQ_2m			144489900UL	// 2m  144.489900 - 144.490100
#define	WSPR_TX_FREQ_none		0UL			// No TX mode

#define		MYTZ				TZ_Europe_Amsterdam	// TZ string for currect location
#define		WSPR_SLOTS_MAX		30			// 30 times 2min slots in a hour

//ESP32
//#define    BUTTON_INPUT    D6      // GPIO 12, INPUT_PULLUP
#define    BUTTON_INPUT    5      // GPIO 12, INPUT_PULLUP

//ESP32
//#define    ONE_WIRE_BUS    D7      // GPIO 13
#define    ONE_WIRE_BUS     4       // GPIO 4





// *********************************************
#include <stdlib.h>
#include <Arduino.h>

#ifndef ESP32
#include <coredecls.h>
#include <TZ.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>    // Include the Wi-Fi-Multi library
#include <sntp.h>
#else
#include <WiFi.h>
#include <WiFiMulti.h>          // Include the Wi-Fi-Multi library
#include <esp_sntp.h>
#include "esp_log.h"
static const char *TAG = "WSPR";
#endif

#include <time.h>
#include <Adafruit_GFX.h>			// Adafruit GFX Library               1.11.5
#include <Adafruit_SSD1306.h>		// Adafruit SSD1306 Wemos Mini OLED
#include <si5351.h>					// Etherkit
#include <JTEncode.h>				// Etherkit
#include <DallasTemperature.h>

#include "WiFi_SSID.h"				// WiFi SSID's from know networks

#ifdef FEATURE_mDNS
#include <ESP8266mDNS.h>
#endif
#ifdef FEATURE_OTA
#include <ArduinoOTA.h>
#endif

#ifdef DEBUG_ESP_PORT
// Put the strings in PROGMEM, slow but free some (constant) ram memory.
 #define PRINT(S)			{ DEBUG_ESP_PORT.print(S); }
 #define PRINT_P(S)			{ DEBUG_ESP_PORT.print(PSTR(S)); }
 #define PRINTF_P(F,...)	{ DEBUG_ESP_PORT.printf_P(PSTR(F), ##__VA_ARGS__); }
#else
 #define PRINT(S)			{ }
 #define PRINT_P(...)		{ }
 #define PRINTF_P(...)		{ }
#endif

#define	SCREEN_WIDTH	128			// OLED display width, in pixels
#define	SCREEN_HEIGHT	64			// OLED display height, in pixels

#define OLED_RESET     -1 	// Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C	///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32, WRORG
Adafruit_SSD1306			display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Si5351						si5351;
JTEncode					wspr;

#ifndef ESP32
static	ESP8266WiFiMulti	wifiMulti;
#else
static  WiFiMulti   wifiMulti;
#endif


// ESP32
//static 	WiFiEventHandler	wifiConnectHandler;						// WiFi connect event handler
//static	WiFiEventHandler	wifiDisconnectHandler;					// WiFi disconnect event handler

// ESP32
const uint8_t     LED_BUILTIN  = 32;   //ESP32



static	String				HostName;
//ESP32
//static	OneWire				oneWire(ONE_WIRE_BUS);					// Temp sensor
//static  DallasTemperature sensors(&oneWire);            // Dallas DS18B20

static	uint8_t				wifi_status_previous	= WL_DISCONNECTED;

//static esp8266::polledTimeout::periodicMs showTimeNow(60000);  	// Checkout

const   uint32_t		value_ms_20ms_loop		= 20;				// 20ms interval check time ntp sec
static  uint32_t		timer_ms_20ms_loop		= 0;
const	uint32_t		value_us_wspr_bit		= 8192.0 / 12000.0 * 1000000.0;	 // Delay value for WSPR
static	uint32_t		timer_us_wspr_bit		= 0;
const	uint32_t		value_us_one_second		= 1000000UL;		// micro second (us)
static	uint32_t		timer_us_one_second		= 0;				// micros()
static	uint32_t		value_ms_display_auto_off;					// Display on time, load per chip
static	uint32_t		timer_ms_display_auto_off;
//const	uint32_t		value_ms_ntp_faild_reboot= 3600 * 1000;		// 1 hour (ntp must be updated in this time)
//static uint32_t		timer_ms_ntp_faild_reboot;
const   uint32_t		value_ms_led_blink_on	= 3141UL;			// 4sec interval blink led
static  uint32_t		timer_ms_led_blink_on	= 0;
const   uint32_t		value_ms_led_blink_off	= 3UL;				// 3ms led on
static  uint32_t		timer_ms_led_blink_off	= 0;

const	uint32_t		sntp_update_delay		= 3600 * 1000UL;	// NTP update every 1h
volatile bool			ntp_time_sync			= false;
static	float			temperature_now			= 0.0;
static  uint8_t			switchStatusLast		= HIGH;				// last status hardware switch
static	enum { DISPLAY_OFF,	DISPLAY_ON } display_status;

static	uint8_t			wspr_symbols[WSPR_SYMBOL_COUNT];
static	uint32_t		wspr_symbol_index		= 0;
static	uint32_t		wspr_tx_counter        	= 0;

static	uint32_t		wspr_slot;									// Slot in the hour, 0..29
static	enum { WSPR_TX_NONE, WSPR_TX_TYPE_1, WSPR_TX_TYPE_2, WSPR_TX_TYPE_3 }
						wspr_slot_tx[WSPR_SLOTS_MAX];				// 0=None, 1="CALL", 2="P/CALL/S", 3="<P/CALL/S>"
static	uint32_t		wspr_slot_band[WSPR_SLOTS_MAX];				// Band freqency, 0 .. 200 Hz
static	uint32_t		wspr_slot_freq[WSPR_SLOTS_MAX][3];			// TX frequency for every CLK output (0..2)

const	uint32_t		wspr_free_second		= 8192.0 / 12000.0 * WSPR_SYMBOL_COUNT + 1.0;

const	int32_t      	wspr_sym_freq[4] =
{	( 0.0 * 12000.0/8192.0 * (float)SI5351_FREQ_MULT + 0.5)
,	( 1.0 * 12000.0/8192.0 * (float)SI5351_FREQ_MULT + 0.5)
,	( 2.0 * 12000.0/8192.0 * (float)SI5351_FREQ_MULT + 0.5)
,	( 3.0 * 12000.0/8192.0 * (float)SI5351_FREQ_MULT + 0.5)
};

static	struct {	int 	ChipId;					// ESP Chip ID
					int 	FreqCorrection;			// Si5351 frequency correction
					int 	RandomSeed;				// Daily pseudo random number, freq
					int		DisplayAutoOff;			// Switch display off timeout
					String	Hostname;				// mDNS & OTA hostname
					float	TempCorrection;			// DS18B20 temp correction, at 18/08/2022
				} ESPChipInfo[] 
=
{	{ 0x7b06f7, 13175,	0x19570215,	1*60000, "WsprTX",		-3.7 }	// Arduino shield, 0x19570215
,	{ 0x62df37, 116860,	0x19561113, 5*60000, "WsprTST",		-1.0 }	// Breadboard
,	{ 0x814A1C, 116860,	0x19561113, 15*60000, "WsprESP32",	 0.0 }	// ESP32 board SDD1306
,	{ -1, 		0,		0X5555,		1*60000, "WsprESP",		 0.0 }	// Default
};

static		int		CHIP_FREQ_CORRECTION;
static		int		CHIP_RANDOM_SEED;
static		int		CHIP_DISPLAY_AUTO_OFF;;
static		String	CHIP_HOSTNAME;
static		float	CHIP_TEMP_CORRECTION;

void ssd1306_text(uint8_t delay_ms, const char* txt1, const char* txt2=NULL);

//
// Make a plan to TX in one of the 30 slots (2min inteval in a hour).
//
void make_slot_plan(bool setup)
{
	int rnd0 = random(20, 180);				// All TX in the hour on the same band
	for (int i = 0; i < WSPR_SLOTS_MAX; i++)
	{
		wspr_slot_tx  [i]		= WSPR_TX_NONE;
		wspr_slot_band[i]		= rnd0;
		wspr_slot_freq[i][0]	= WSPR_TX_FREQ_0;
		wspr_slot_freq[i][1]	= WSPR_TX_FREQ_1;
		wspr_slot_freq[i][2]	= WSPR_TX_FREQ_2;
	}

#ifdef FEATURE_1H_FAST_TX
	if (setup)
	{
		// Every odd slot a TX until the first hour.
		for (int i = 0; i < WSPR_SLOTS_MAX; i += 6)
		{
			wspr_slot_tx[i+0] = WSPR_TX_TYPE_2;	// 0 - Min:  0, 12, 24, 36, 48
			wspr_slot_tx[i+1] = WSPR_TX_NONE;	// 1 - Min:  2, 14, 26, 38, 50
			wspr_slot_tx[i+2] = WSPR_TX_TYPE_2;	// 2 - Min:  4, 16, 28, 40, 52
			wspr_slot_tx[i+3] = WSPR_TX_TYPE_3;	// 3 - Min:  6, 18, 30, 42, 54
			wspr_slot_tx[i+4] = WSPR_TX_NONE;	// 4 - Min:  8, 20, 32, 44, 56
			wspr_slot_tx[i+5] = WSPR_TX_NONE;	// 5 - Min: 10, 22, 34, 46, 58
		}
	}
	else
#endif

#if 1
	{
		// Even slot 40m, PA3EDR testing.
		int bnd = 25;					// Use audio band 25--175 Hz
		for (int i = 0; i < WSPR_SLOTS_MAX; 
				i += 1)
//				i += 2)
		{
			wspr_slot_band[i]		= bnd;
			bnd += 5;
			if (bnd >= 175) bnd = 25; 	// Step size if 5 Hz
			wspr_slot_tx  [i]		= WSPR_TX_TYPE_2;
			wspr_slot_freq[i][0]	= i & 1 ? WSPR_TX_FREQ_20m : WSPR_TX_FREQ_40m;
		}

		// TX ones every hour the 6 char QTH locator.	
		wspr_slot_tx  [2]			= WSPR_TX_TYPE_3;
	}
//#elif 1
	{
		int   s0,s1,s2,s3,t;
		float tf;

		ReadTemperature();

		//Convert temperature to integer value
		// >-20 ... <50 ==> 0 ... 70 ==> *10 = 0 ... 700
		tf = temperature_now + 20.0;			//== Negative start offset
		if (tf < 0.0) tf = 0.0;
		if (tf >= 70.0) tf = 70.0 - 0.1;
		tf *= 10;								//== Decimal steps
		t = (int)(tf + 0.5);					// Rounding

		s1 =  0 + t / 100;	t %= 100;			// 0-6 :  0 .. 12 min
		s2 = 10 + t /  10;	t %= 10;			// 0-9 : 20 .. 38 min
		s3 = 20 + t /   1;						// 0-9 : 40 .. 58 min
		s0 = s1 + 1;							// After first digit tx

		PRINTF_P("TX Slots: loc[%d], temp[%d, %d, %d]\n", s0, s1, s2, s3);

//		wspr_slot_tx[s0]		= WSPR_TX_TYPE_3;	// TX locator 6
		wspr_slot_tx[s1]		= WSPR_TX_TYPE_2;	// Comp, no locator
		wspr_slot_tx[s2]		= WSPR_TX_TYPE_2;	// Comp, no locator
		wspr_slot_tx[s3]		= WSPR_TX_TYPE_2;	// Comp, no locator

//		wspr_slot_freq[s0][0]	= WSPR_TX_FREQ_30m;
		wspr_slot_freq[s1][0]	= WSPR_TX_FREQ_30m;
		wspr_slot_freq[s2][0]	= WSPR_TX_FREQ_30m;
		wspr_slot_freq[s3][0]	= WSPR_TX_FREQ_30m;
	}
#endif

#ifdef FEATURE_PRINT_TIMESLOT
	PRINT_P("Time Slot:\n");
	for(uint8_t i=0; i < WSPR_SLOTS_MAX; ++i) {
		if (wspr_slot_tx[i] != WSPR_TX_NONE)
			PRINTF_P("\t%02d:wspr%d-%d+%d\n", i, wspr_slot_tx[i], wspr_slot_freq[i], wspr_slot_band[i]);
	}
	PRINT_P("\n");
#endif
}

uint32_t sntp_update_delay_MS_rfc_not_less_than_15000 ()
{
    return sntp_update_delay;
}

//---------------------------------------------------------------------------------
//---- SETUP....  SETUP....  SETUP....  SETUP....  SETUP....
//---------------------------------------------------------------------------------
void setup()
{
	//ESP32
	// Find the ESP chip-id specific data.
#ifdef ESP8266
	int i = 0, chipid = ESP.getChipId();
#else
	int i = 0, chipid = 0;
	for (int i = 0; i < 17; i = i + 8) 
	{
		chipid |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
	}
	ESP_LOGI(TAG, "ESP32 ChipID = %X", chipid);
#endif
  
	while(true)
	{
		CHIP_FREQ_CORRECTION 	= ESPChipInfo[i].FreqCorrection;
		CHIP_RANDOM_SEED     	= ESPChipInfo[i].RandomSeed;
		CHIP_DISPLAY_AUTO_OFF	= ESPChipInfo[i].DisplayAutoOff;
		CHIP_HOSTNAME			= ESPChipInfo[i].Hostname;
		CHIP_TEMP_CORRECTION	= ESPChipInfo[i].TempCorrection;
		if (ESPChipInfo[i].ChipId == chipid || ESPChipInfo[i].ChipId == -1) break;
		i++;
	}
	randomSeed(CHIP_RANDOM_SEED);
	value_ms_display_auto_off = CHIP_DISPLAY_AUTO_OFF;
	HostName = CHIP_HOSTNAME;

	Serial.begin(115200);				// 115200
	Serial.setTimeout(2000);
	while(!Serial) yield();
#ifdef DEBUG_ESP_PORT
	Serial.setDebugOutput(true);
#endif
	delay(1000);

	PRINT_P("\n=== PE0FKO, TX WSPR temperature coded\n");
	PRINTF_P ("=== Version: " VERSION ", Build at: %s %s\n", __TIME__, __DATE__);
	PRINTF_P ("=== Config: " HAM_PREFIX HAM_CALL HAM_SUFFIX " - " HAM_LOCATOR " - %ddBm\n", HAM_POWER);

	PRINTF_P("Sizeof int      : %d\n", sizeof(int));
	PRINTF_P("Sizeof long     : %d\n", sizeof(long));
	PRINTF_P("Sizeof long long: %d\n", sizeof(long long));

	PRINTF_P("value_us_wspr_bit: %ld\n", value_us_wspr_bit);


	PRINTF_P("SSD1306: %dx%d addr:0x%02x\n", SSD1306_LCDHEIGHT, SSD1306_LCDWIDTH, 0x3C);
  //  Wire.begin();   // SCL=GPIO22 ; SDA =GPIO21
  Wire.begin(I2C_SDA, I2C_SCL);

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);

  display.display();  // Display splash screen "Adafruit"
  delay(1000);

//	display.setRotation(2);						// Display upside down...

	pinMode(BUTTON_INPUT, INPUT_PULLUP);		// Button for display on/off
	ssd1306_display_on();						// Start the display ON timer

//  Serial.println("=====================================: 1 :----------------");

	pinMode(LED_BUILTIN, OUTPUT);				// BuildIn LED

	ssd1306_text(1000, "Hostname", HostName.c_str());

	// WiFi settings
	WiFi.mode(WIFI_STA);						// Set WiFi to station mode

	WiFi.setHostname(HostName.c_str());			// Set Hostname.
//	wifi_station_set_hostname(HostName.c_str());

	WiFi.setAutoReconnect(true);				// Keep WiFi connected


//ESP32
	// Register WiFi event handlers
//	WiFi.onEvent(onWifiEvent);
//	wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
//	wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);


//  WiFi.onEvent(WiFiStationConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(WiFiGotIP, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(WiFiStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);





	// Try to startup the WiFi Multi connection with the strongest AP found.
	for(i = 0; i < WifiApListNumber; i++)
		wifiMulti.addAP(WifiApList[i].ssid, WifiApList[i].passwd);

#ifdef FEATURE_mDNS
	init_mdns();						// Init the broadcast DNS server (.local)
#endif

#ifdef FEATURE_OTA
	// Start OTA server.
	ArduinoOTA.setHostname((const char *)HostName.c_str());
	ArduinoOTA.onStart([]() { ssd1306_text(200,  "Running", "OTA update"); });
	ArduinoOTA.onEnd([]()   { ssd1306_text(2000, "Reboot",  "OTA update"); ESP.restart(); });
	ArduinoOTA.setPassword("123");
	ArduinoOTA.begin();
#endif

//	sensors.begin();					// Init the onewire for the DS18B20 temp sensor
	ReadTemperature();					// Read the Dallas temperature one-wire sensor

	init_si5351();						// Init the frequency generator SI5351

	make_slot_plan(true);				// The first hour slot plan definition

	struct timeval	tv;
	gettimeofday(&tv, NULL);			// Get the current time in usec
	PRINT(ctime(&tv.tv_sec));			// convert timestamp and display

	pinMode(LED_BUILTIN, OUTPUT);		// LED on the ESP
	digitalWrite(LED_BUILTIN, HIGH);	// High is off!

#ifdef FEATURE_CARRIER
//#if 1
	si5351.set_freq( SI5351_FREQ_MULT * 7040100, SI5351_CLK0 );
	wspr_tx_enable(SI5351_CLK0);

//	si5351.set_freq( SI5351_FREQ_MULT * wspr_slot_freq[0][0], SI5351_CLK0 );
//	wspr_tx_enable(SI5351_CLK0);
//	si5351.set_freq( SI5351_FREQ_MULT * wspr_slot_freq[0][1], SI5351_CLK1 );
//	wspr_tx_enable(SI5351_CLK1);
//	si5351.set_freq( SI5351_FREQ_MULT * wspr_slot_freq[0][2], SI5351_CLK2 );
//	wspr_tx_enable(SI5351_CLK2);

//	PRINTF_P("CW Carrier on: %fMHz\n", (float)(WSPR_TX_FREQ + 100)/1e6);
#endif

	ssd1306_text(200, "Start", "looping");
	PRINT_P("=== Start looping...\n");

	ssd1306_main_window();
}



//void onWifiConnect(const WiFiEventStationModeConnected& ssid)
//{
//	PRINTF_P("WiFi connected: SSID %s\n", ssid.ssid.c_str());
//}


// callback routine - arrive here whenever a successful NTP update has occurred
//ESP32
//void sntp_time_is_set(bool from_sntp)
void sntp_time_is_set()
{
	time_t now = time(nullptr);          // get UNIX timestamp
	PRINT_P("NTP update done at:: ");
	PRINT(ctime(&now));

	ESP_LOGI(TAG, "NTP update done at: %s", ctime(&now));

	ntp_time_sync = true;
}

void time_sync_notification_cb(struct timeval *tv)
{
    ESP_LOGI(TAG, "Notification of a time synchronization event");
    sntp_time_is_set();
}

//ESP32

void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info)
{
	Serial.print("WiFi connected IP address: ");
	Serial.println(WiFi.localIP());

//ESP32

	ESP_LOGI(TAG, "Initializing SNTP");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_set_time_sync_notification_cb(time_sync_notification_cb);
#ifdef CONFIG_SNTP_TIME_SYNC_METHOD_SMOOTH
    sntp_set_sync_mode(SNTP_SYNC_MODE_SMOOTH);
#endif
    sntp_init();

//  settimeofday_cb(sntp_time_is_set);      // Call-back function
//  configTime(MYTZ, "time.google.com","nl.pool.ntp.org");

//  esp_sntp_init();

  ntp_time_sync = false;

//  timer_ms_ntp_faild_reboot = millis();
}

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  sntp_stop();
//  timer_ms_ntp_faild_reboot = millis();

  Serial.println("Disconnected from WiFi access point");
  Serial.print("WiFi lost connection. Reason: ");
  Serial.println(info.wifi_sta_disconnected.reason);
  Serial.println("Trying to Reconnect");
//  WiFi.begin(ssid, password);
  WiFi.begin();
}

#if 0
void onWifiConnect(const WiFiEventStationModeGotIP& ipInfo)
{
	PRINTF_P("WiFi connected: IP:%s/%s GW:%s\n",
		ipInfo.ip.toString().c_str(),
		ipInfo.mask.toString().c_str(),
		ipInfo.gw.toString().c_str()
		);

	settimeofday_cb(sntp_time_is_set);			// Call-back function
	configTime(MYTZ, "time.google.com","nl.pool.ntp.org");

	sntp_init();

	ntp_time_sync = false;

//	timer_ms_ntp_faild_reboot = millis();
}

void XXXXonWifiDisconnect(const WiFiEventStationModeDisconnected& disconnectInfo)
{
  sntp_stop();
//  timer_ms_ntp_faild_reboot = millis();

  PRINTF_P("WiFi disconnected from SSID: %s, Reason: %d\n",
      disconnectInfo.ssid.c_str(),
    disconnectInfo.reason
    );
}

#endif

void ReadTemperature()
{
//ESP32
//	sensors.requestTemperatures();
//  temperature_now = sensors.getTempCByIndex(0) + CHIP_TEMP_CORRECTION;
  temperature_now = 20.4;

	PRINTF_P("Sensor DS18B20 temperature %.1fºC\n", temperature_now);
}

#ifdef FEATURE_mDNS
static void init_mdns()
{
	ssd1306_text(200, "mDNS", "Setup");
	if (MDNS.begin(HostName.c_str()))
		MDNS.addService("http", "tcp", 80);
	else
		PRINT_P("mDNS ERROR!\n");
}
#endif

//---------------------------------------------------------------------------------
//---- LOOP....  LOOP....  LOOP....  LOOP....  LOOP....
//---------------------------------------------------------------------------------
void loop()
{


#if 1

	
	loop_wspr_tx();
	loop_1s_tick();
	loop_20ms_tick();
	loop_wifi_tick();
	loop_led_tick();

	#ifdef FEATURE_OTA
	ArduinoOTA.handle();
	#endif

	#ifdef FEATURE_mDNS
	MDNS.update();
	#endif

#if 0
	// Wait for the NTP time service is known!
	if (!ntp_time_sync)
	{
		if ((millis() - timer_ms_ntp_faild_reboot) >= value_ms_ntp_faild_reboot)
		{
			ssd1306_text(2000, "REBOOT", "NTP sync...");
			PRINT_P("REBOOT: No NTP time received.\n");
			Serial.flush();
			ESP.restart();
		}

// Maak langere loops met timer
//		ssd1306_text(500, "Waiting", "NTP sync");
//		return;		// Return the loop!!
	}
#endif


#endif
}

void loop_wspr_tx()
{
	// Send the WSPR bits into the air if active TX!
	// When started it will wait for the bit time and start a next bit.

#if 1
	if (wspr_symbol_index != 0) 
	{
		uint32_t	diff = micros() - timer_us_wspr_bit;
		if (diff >= value_us_wspr_bit)
		{
			timer_us_wspr_bit += value_us_wspr_bit;
			wspr_tx_bit();										// Ok, transmit the net tone bit

			if (diff >= (value_us_wspr_bit+500UL))
			{
				Serial.printf("WSPT-Bit %u overflow %ld us.\n", wspr_symbol_index, diff - value_us_wspr_bit);
			}
		}
	}
#else
	if ((wspr_symbol_index != 0) 
	&&  (micros() - timer_us_wspr_bit) >= value_us_wspr_bit)
	{
		timer_us_wspr_bit += value_us_wspr_bit;
		wspr_tx_bit();										// Ok, transmit the net tone bit
	}
#endif
}

// Secure one second function call
void loop_1s_tick() 
{
	if ((micros() - timer_us_one_second) >= value_us_one_second)
	{
		if (timer_us_one_second == 0)			// Initialize the timer only ones!
			timer_us_one_second = micros();

		struct timeval tv;
		gettimeofday(&tv, NULL);				// Get the current time in usec
		if (tv.tv_usec > 500000UL)				// Over the half second, wait for second end
		{
			timer_us_one_second +=				// Set the (usec=1000000) timer for one second clock
				1000000UL - tv.tv_usec;			// Still need to wait the last part of us
		}
		else
		{
			// On time or to late, both run the sec loop.
			timer_us_one_second +=	value_us_one_second - tv.tv_usec;

//			Serial.printf("Time: %6u: %s", tv.tv_usec, ctime(&tv.tv_sec));

			loop_1s_tick_wspr(
				tv.tv_sec % (3600 * 24)	/ 3600,
				tv.tv_sec % (3600) 		/ 120,
				tv.tv_sec % (120)
			);

			loop_1s_tick_clock(
				tv.tv_sec % (120)
			);
		}
	}
}


// Used for slower processing, timing from the cpu xtal
void loop_20ms_tick() 
{
	if ((millis() - timer_ms_20ms_loop) >= value_ms_20ms_loop)	// Every 20ms...
	{
		if (timer_ms_20ms_loop == 0) {
			timer_ms_20ms_loop = millis();
			return;
		}

		timer_ms_20ms_loop += value_ms_20ms_loop;

		time_t		now			= time(nullptr);
		uint16_t	sec			= now % 60;

		// Check if button is pressed to lightup the display
		int switchStatus = digitalRead(BUTTON_INPUT);		// read status of switch
		if (switchStatus != switchStatusLast)				// if status of button has changed
		{
			  switchStatusLast = switchStatus;
			  if (switchStatus == LOW)
			  {
				display_status = display_status == DISPLAY_ON ? DISPLAY_OFF : DISPLAY_ON;

				if (display_status == DISPLAY_ON)
				{
					ssd1306_display_on();				  	// Start the display ON timer
					digitalWrite(LED_BUILTIN, HIGH);		// Switch the ESP LED off
					ReadTemperature();						// Get temperature
					ssd1306_main_window();					// Write to display
				}
				else
					ssd1306_display_off();

				PRINTF_P("Button pressed, display_status=%d\n", display_status);
			  }
		}
#if 0
		// Blink the ESP LED every 4s if display is off
		if (display_status == DISPLAY_OFF)
		{
			static uint8_t led_pwm;
			led_pwm %= 200;
			digitalWrite(LED_BUILTIN, led_pwm++ == 0 ? LOW : HIGH);
			delay(3);
			digitalWrite(LED_BUILTIN, HIGH);
		}
#endif
	}   		// 50Hz code lus
}

void loop_wifi_tick() 
{
	if (wspr_symbol_index == 0)
	{
//		wifiMulti.run((120 - 1 - wspr_free_second) * 1000UL);

		if (wifiMulti.run((120 - 1 - wspr_free_second) * 1000UL) == WL_CONNECTED)
		{
			if (timer_ms_led_blink_on == 0)
				timer_ms_led_blink_on = millis();
		}
		else
		{
			timer_ms_led_blink_on = 0;
		}
	}
}


void loop_led_tick() 
{
	if (timer_ms_led_blink_on != 0
	&&  (millis() - timer_ms_led_blink_on) >= value_ms_led_blink_on)
	{
		timer_ms_led_blink_on += value_ms_led_blink_on;
		digitalWrite(LED_BUILTIN, LOW);					// LED On
		timer_ms_led_blink_off = millis();
	}

	if (timer_ms_led_blink_off != 0
	&&	(millis() - timer_ms_led_blink_off) >= value_ms_led_blink_off)
	{
		timer_ms_led_blink_off = 0;
		digitalWrite(LED_BUILTIN, HIGH);				// LED Off
	}
}

void loop_1s_tick_wspr(uint8_t hour, uint8_t slot, uint8_t slot_sec)
{
	//
	//++ At every 2 minute interval start a WSPR message, if slot is richt.
	//
	if (slot_sec == 0)										// First second of the 2 minute interval clock
	{
		wspr_slot = slot;

		if (wspr_slot == 0)
			make_slot_plan(false);

		Serial.printf("WSPR-Time: %2u:%02u:%03u\n", hour, wspr_slot, slot_sec);

		if (wspr_slot_tx[wspr_slot] == WSPR_TX_TYPE_1)			// Type 1 message: CALL, LOC4, dBm
			wspr_tx_init(HAM_CALL);

		else if (wspr_slot_tx[wspr_slot] == WSPR_TX_TYPE_2)		// Type 2 message: pre/CALL/suff, dBm
			wspr_tx_init(HAM_PREFIX HAM_CALL HAM_SUFFIX);

		else if (wspr_slot_tx[wspr_slot] == WSPR_TX_TYPE_3)		// Type 3 message: hash <pre/CALL/suff>, LOC6, dBm
			wspr_tx_init("<" HAM_PREFIX HAM_CALL HAM_SUFFIX ">");
	}

	//++ Set the random seed ones every day.
	//   Posible track of (semi) random numbers!
	if (hour == 23 && slot == 29 && slot_sec == wspr_free_second)
	{
		PRINTF_P("Set the const ramdom seed number 0x%08x\n", CHIP_RANDOM_SEED);
		randomSeed(CHIP_RANDOM_SEED);
	}
}

void loop_1s_tick_clock(uint8_t slot_sec)
{
	// Only read the temp once every 2min
	if (display_status == DISPLAY_ON && slot_sec == wspr_free_second) 
		ReadTemperature();

	ssd1306_main_window();
}

static void init_si5351()
{
	PRINTF_P("Si5351 init: xtal:%d, correction:%d\n", SI5351_XTAL_FREQ, CHIP_FREQ_CORRECTION);

	ssd1306_text(200, "Si5351", "Setup");

	if ( si5351.init(SI5351_CRYSTAL_LOAD_8PF, SI5351_XTAL_FREQ, CHIP_FREQ_CORRECTION) )
	{
		// Disable the clock initially...
		wspr_tx_disable(SI5351_CLK0);
		wspr_tx_disable(SI5351_CLK1);
		wspr_tx_disable(SI5351_CLK2);

		ssd1306_text(200, "Si5351", "OK");
	}
	else
		ssd1306_text(200, "Si5351", "Not found");
}

void wspr_tx_init(const char* call)
{
	PRINTF_P("WSPR TX with Call: %s, Loc:%s, Power:%ddBm\n", call, HAM_LOCATOR, HAM_POWER);

	wspr.wspr_encode(call, HAM_LOCATOR, HAM_POWER, wspr_symbols);
#ifdef FEATURE_PRINT_WSPR_SIMBOLS
	print_wspr_symbols(call, HAM_LOCATOR, HAM_POWER, wspr_symbols);
#endif

	timer_us_wspr_bit = micros();
	wspr_tx_bit();
}

#ifdef FEATURE_PRINT_WSPR_SIMBOLS
// "PE0FKO JO32 10"
// SYMBOL: 3,3,2,0,2,2,0,2,3,0,2,2,3,3,3,0,0,0,1,2,0,1,2,3,1,1,3,2,0,2,2,2,2,0,1,2,0,1,2,3,2,0,0,0,2,0,3,0,1,1,2,2,1,3,0,3,0,2,2,3,1,2,1,0,0,2,0,3,1,2,1,0,3,0,3,0,1,0,0,1,0,0,1,2,3,1,2,0,2,3,1,2,3,2,3,2,0,2,1,2,0,0,0,0,1,2,2,1,2,0,1,3,1,2,3,1,2,0,1,3,2,3,0,2,0,3,1,1,2,0,2,2,2,1,0,1,2,2,3,3,0,2,2,2,2,2,2,1,1,2,1,0,1,3,2,2,0,1,3,2,2,2
void print_wspr_symbols(const char* call, const char* loc, uint8_t power, uint8_t symbols[])
{
	PRINTF_P("%s %s %ddBm:\n  ", call, loc, power);
	for (uint8_t i = 0; i < WSPR_SYMBOL_COUNT; )
	{
		PRINTF_P("%d,", symbols[i++]);
		if (i % 41 == 0) PRINT_P("\n  ");
	}
	PRINT_P("\n");
}
#endif

void wspr_tx_bit()
{
	if (wspr_symbol_index != WSPR_SYMBOL_COUNT)
	{
		if (wspr_symbol_index == 0)   // On first bit enable the tx output.
		{
			wspr_tx_enable(SI5351_CLK0);
			wspr_tx_enable(SI5351_CLK1);
			wspr_tx_enable(SI5351_CLK2);
		}

		wspr_tx_freq(SI5351_CLK0);
		wspr_tx_freq(SI5351_CLK1);
		wspr_tx_freq(SI5351_CLK2);

		wspr_symbol_index += 1;
	}
	else
	{
		wspr_tx_disable(SI5351_CLK0);
		wspr_tx_disable(SI5351_CLK1);
		wspr_tx_disable(SI5351_CLK2);

		wspr_symbol_index = 0;
		wspr_tx_counter += 1;

		PRINTF_P("TX WSPR %d Ended.\n", wspr_tx_counter);
	}
}

void wspr_tx_freq(si5351_clock clk)
{
	if (wspr_slot_tx[wspr_slot] != WSPR_TX_NONE && 
	    wspr_slot_freq[wspr_slot][clk] != 0)
	{
		uint64_t wspr_frequency = SI5351_FREQ_MULT * (wspr_slot_freq[wspr_slot][clk] + wspr_slot_band[wspr_slot]);
		if (si5351.set_freq( wspr_frequency + wspr_sym_freq[wspr_symbols[wspr_symbol_index]], clk ) )
			PRINTF_P("ERROR: wspr_tx_freq(%d) / SI5351::set_freq(...)\n", clk);
	}
}

void wspr_tx_enable(si5351_clock clk)
{
	if (wspr_slot_tx[wspr_slot] != WSPR_TX_NONE && 
	    wspr_slot_freq[wspr_slot][clk] != 0)
	{
		PRINTF_P("TX WSPR start %d: slot %d, freq %.6fMHz + %dHz\n", 
				clk, wspr_slot, 
				wspr_slot_freq[wspr_slot][clk] / 1000000.0, 
				wspr_slot_band[wspr_slot]);

		si5351.drive_strength(clk, SI5351_DRIVE_8MA); // 2mA= dBm, 4mA=3dBm, 6mA= dBm, 8mA=10dBm
		si5351.set_clock_pwr(clk, 1);
		si5351.output_enable(clk, 1);
	}
 }

void wspr_tx_disable(si5351_clock clk)
{
	si5351.set_clock_pwr(clk, 0);
	si5351.output_enable(clk, 0);
}

void ssd1306_main_window()
{
	struct timeval	tv;
	char			buffer[30];
	struct tm*		timeinfo;
	int16_t   		x,y;
	uint16_t  		w,h;
	int				ns = wspr_slot;	// next slot


	if (display_status == DISPLAY_OFF)
		return;

	if ((millis() - timer_ms_display_auto_off) >= value_ms_display_auto_off)
	{
		ssd1306_display_off();
		return;
	}

	gettimeofday(&tv, NULL);			// Get the current time in usec

	ssd1306_background();

	if (ntp_time_sync)
	{
		timeinfo = localtime (&tv.tv_sec);
		strftime (buffer ,sizeof buffer ,"%H:%M:%S", timeinfo);
		display.setTextSize(2);
		w = getFontStringWidth(buffer);
		display.setCursor((display.width() - w) / 2 , 12);
		display.print(buffer);

		strftime (buffer ,sizeof buffer ,"- %d/%m/%Y -", timeinfo);
		display.setTextSize(1);
		w = getFontStringWidth(buffer);
		display.setCursor((display.width() - w) / 2 , 32);
		display.print(buffer);
	}
	else
	{
		if (WiFi.status() != WL_CONNECTED)
			strcpy(buffer, "WiFi disconnect");
		else
			strcpy(buffer, "sNTP Waiting");

		display.setTextSize(1);
		w = getFontStringWidth(buffer);
		display.setCursor((display.width() - w) / 2 , 16+2);
		display.print(buffer);

		strcpy(buffer, "- Syncing -");

		display.setTextSize(1);
		w = getFontStringWidth(buffer);
		display.setCursor((display.width() - w) / 2 , 32-2);
		display.print(buffer);
	}

	sprintf(buffer, "%s/%s/%ddBm", HAM_CALL, HAM_LOCATOR, HAM_POWER);
	w = getFontStringWidth(buffer);
	display.setCursor((display.width()- w)/2, display.height()-10);
	display.print(buffer);

	if (wspr_symbol_index != 0)
	{
		uint16_t B,E;
		B = 4;
		E = B + tv.tv_sec % 120;
		display.drawLine(B, display.height()-14, E, display.height()-14, WHITE);
		display.drawLine(B, display.height()-16, E, display.height()-16, WHITE);

		// At TX invert the display collors
		display.invertDisplay(true);
	}
	else
	{
		// Calculate the next tx time and slot
		uint16_t w = 120 - (tv.tv_sec % 120);
		while (wspr_slot_tx[ns++] == WSPR_TX_NONE) 
		{
			if (ns >= WSPR_SLOTS_MAX) ns = 0;
			w += 120;
		}
		if (w < 3600)
		{
			// Display time next tx
			sprintf(buffer, "TX %02d:%02d", w/60, w%60);
			display.setCursor(14, display.height()-20);
			display.print(buffer);
		}

		// The actual temperature used
		sprintf(buffer, "%.1f", temperature_now);
		w = getFontStringWidth(buffer);
		display.setCursor(display.width() - 14 - w, display.height()-20);
		display.print(buffer);

		// Non TX normal display
		display.invertDisplay(false);
	}

	// Display the used freq bands
	sprintf(buffer, "%s/%s/%s"
			, wspr_slot_freq[ns][0] == 0 ? "x" : String(300/(wspr_slot_freq[ns][0]/1000000)).c_str()
			, wspr_slot_freq[ns][1] == 0 ? "x" : String(300/(wspr_slot_freq[ns][1]/1000000)).c_str()
			, wspr_slot_freq[ns][2] == 0 ? "x" : String(300/(wspr_slot_freq[ns][2]/1000000)).c_str()
			);

	display.getTextBounds(buffer, 0, 0, &x, &y, &w, &h);
	x = display.width() * 1 / 4;
	x -= w / 2; if (x < 10) x = 10;
	display.fillRect(x, y, w, h, BLACK);
	display.setCursor(x, y);
	display.print(buffer);

	display.display();
}

void ssd1306_background()
{
	char buf_count[20];
	int16_t   x, y;
	uint16_t  w, h;

	sprintf(buf_count, "%d", wspr_tx_counter);

	display.setTextSize(1);
	display.setTextColor(WHITE);

	display.getTextBounds(buf_count, 0, 0, &x, &y, &w, &h);

	display.clearDisplay();
	display.drawRoundRect(x, h/2-1, display.width(), display.height() - h/2-1, 8, WHITE);

	x = display.width() * 3 / 4;
	x -= w / 2;
	display.fillRect(x, y, w, h, BLACK);
	display.setCursor(x, y);
	display.print(buf_count);
}

void ssd1306_display_on()
{
	PRINTF_P("Display On for %dsec.\n", value_ms_display_auto_off/1000);
	timer_ms_display_auto_off = millis();		// Start the display ON timer
	display_status  = DISPLAY_ON;
}

void ssd1306_display_off()
{
	PRINTF_P("Display auto Off at %d sec.\n", value_ms_display_auto_off/1000);

	display.clearDisplay();
	display.invertDisplay(false);
	display.display();
	display_status = DISPLAY_OFF;
}

uint16_t getFontStringWidth(const String& str)
{
	int16_t   x, y;
	uint16_t  w, h;
	display.getTextBounds(str, 0, 0, &x, &y, &w, &h);
	return w;
}

void ssd1306_text(uint8_t delay_ms, const char* txt1, const char* txt2)
{
	ssd1306_background();

	display.setTextSize(1);
	if (txt1 != NULL)
	{
		uint16_t  w = getFontStringWidth(txt1);
		display.setCursor((display.width() - w) / 2 , 16);
		display.print(txt1);
	}
	if (txt2 != NULL)
	{
		uint16_t  w = getFontStringWidth(txt2);
		display.setCursor((display.width() - w) / 2 , 16+16);
		display.print(txt2);
	}

	if (WiFi.SSID().length() > 0)
	{
		String ssid("SSID:"); ssid += WiFi.SSID();
		uint16_t  w = getFontStringWidth(ssid);
		display.setCursor((display.width() - w) / 2 , 52);
		display.print(ssid);
	}

	ssd1306_display_on();
	display.display();

	PRINTF_P("ssd1306_text[%d]: ", delay_ms);
	if (txt1 != NULL)	PRINT(txt1);
	if (txt2 != NULL) {	PRINT_P(" / "); PRINT(txt2); }
	PRINT_P("\n");

	if (delay_ms >= 0)
		delay(delay_ms);
}

void ssd1306_wifi_page()
{
	PRINTF_P("Connected to %s (IP:%s/%s, GW:%s, RSSI %d)\n"
		, WiFi.SSID().c_str()
		, WiFi.localIP().toString().c_str()				// Send the IP address of the ESP8266 to the computer
		, WiFi.subnetMask().toString().c_str()
		, WiFi.gatewayIP().toString().c_str()
		, WiFi.RSSI());

	ssd1306_background();
	display.setTextSize(1);

	display.setCursor(6, 16+10*0);
 	display.printf("SSID:%s", WiFi.SSID().c_str());
	display.setCursor(6, 16+10*1);
 	display.printf("  IP:%s", WiFi.localIP().toString().c_str());
	display.setCursor(6, 16+10*2);
 	display.printf("RSSI:%d", WiFi.RSSI());

	ssd1306_display_on();
	display.display();

	delay(2000);
}
