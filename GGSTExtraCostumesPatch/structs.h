typedef int8_t s8;
typedef uint8_t u8;
typedef int16_t s16;
typedef uint16_t u16;
typedef int32_t s32;
typedef uint32_t u32;
typedef int64_t s64;
typedef uint64_t u64;
typedef float f32;
typedef double f64;

typedef struct
{
    u64 charID;
    wchar_t* Name;
} FCharaID;

typedef struct
{
    FCharaID CharacterTables[40];
} GlobalCharTables;

typedef enum SIDE_ID {
    SIDE_1P = 0,
    SIDE_BEGIN = 0,
    SIDE_2P = 1,
    SIDE_COMMON = 2,
    SIDE_ID_NUM = 2,
    SIDE_ID_NUM_WITH_COMMON = 3,
    SIDE_ID_INVALID = 4
} SIDE_ID;

typedef enum EMemberID {
    MemberID_01 = 0,
    MemberID_Begin = 0,
    MemberID_02 = 1,
    MemberID_03 = 2,
    MemberID_MAX = 3,
    MemberID_INVALID = 4
} EMemberID;

struct FString {
    wchar_t* Name;
    int min;
    int max;
};

struct IDConvertTable {
    int SourceID;
    int DestID;
};

typedef struct
{
	u8 Select;
	u8 Start;
	u8 DPadUp;
	u8 DPadRight;
	u8 DPadDown;
	u8 DPadLeft;
	u8 L1;
	u8 R1;
	u8 L2;
	u8 R2;
	u8 L3;
	u8 R3;
	u8 Circle;
	u8 Cross;
	u8 Square;
	u8 Triangle;
	u8 RightStickUp;
	u8 RightStickRight;
	u8 RightStickDown;
	u8 RightStickLeft;
	f32 LeftStickXPos;
	f32 LeftStickYPos;
	f32 RightStickXPos;
	f32 RightStickYPos;
	f32 LeftTriggerDepth;
	f32 RightTriggerDepth;
}UE4PlayerInput;

typedef struct FSpawnPlayerInfo
{
    SIDE_ID SideID;                     // 0x0
    EMemberID MemberID;                 // 0x4
    FString CharaID;                    // 0x8
    FString SelfTeamMemberCharaID;      // 0x18
    FString EnemyTeamMemberCharaID;     // 0x28
    FString BGLayerNames;               // 0x38
    u32 CostumeID;                      // 0x48
    u32 ColorID;                        // 0x4C
    u32 ScriptType;                     // 0x50
    u32 Field54;                        // 0x54
    FString VoiceLoc;                   // 0x58
    u8 bREV2ModelFlag;                  // 0x68
    u8 Field69;                         // 0x69
    u8 Field6A;                         // 0x6A
    u8 Field6B;                         // 0x6B
    u32 Field6C;                        // 0x6C
    IDConvertTable* CostumeIDConvTable; // 0x70
    IDConvertTable* ColorIDConvTable;   // 0x78
    u32 CostumeIDConvTableNum;          // 0x80
    u32 ColorIDConvTableNum;            // 0x84
} FSpawnPlayerInfo;

typedef struct CSS_INFO
{
    u32 field00;
    u32 field04;
    u32 field08;
    u32 field0c;
    u32 field10;
    u32 field14;
    u32 field18;
    u32 field1c;
    u32 field20;
    u32 field24;
    u32 field28;
    u32 field2c;
    u32 field30;
    u32 field34;
    u32 field38;
    u32 field3c;
    u32 field40;
    u32 field44;
    u32 field48;
    u32 field4c;
    u32 field50;
    u32 field54;
    u32 field58;
    u32 field5c;
    u32 field60;
    u32 field64;
    u32 field68;
    u32 field6c;
    u32 field70;
    u32 field74;
    u32 field78;
    u32 field7c;
    u32 field80;
    u32 field84;
    u32 field88;
    u32 field8c;
    u32 field90;
    u32 field94;
    u32 field98;
    u32 field9c;
    u32 fielda0;
    u32 fielda4;
    u32 fielda8;
    u32 fieldac;
    u32 fieldb0;
    u32 fieldb4;
    u32 fieldb8;
    u32 fieldbc;
    u32 fieldc0;
    u32 fieldc4;
    u32 fieldc8;
    u32 fieldcc;
    u32 fieldd0;
    u32 fieldd4;
    u32 fieldd8;
    u32 fielddc;
    u32 fielde0;
    u32 fielde4;
    u32 fielde8;
    u32 fieldec;
    u32 fieldf0;
    u32 fieldf4;
    u32 fieldf8;
    u32 fieldfc;
    u32 field100;
    u32 field104;
    u32 field108;
    u32 field10c;
    u32 field110;
    u32 field114;
    u32 field118;
    u32 field11c;
    u32 field120;
    u32 field124;
    u32 field128;
    u32 field12c;
    u32 field130;
    u32 field134;
    u32 field138;
    u32 field13c;
    u32 field140;
    u32 field144;
    u32 field148;
    u32 field14c;
    u32 field150;
    u32 field154;
    u32 field158;
    u32 field15c;
    u32 field160;
    u32 field164;
    u32 field168;
    u32 field16c;
    u32 field170;
    u32 field174;
    u32 field178;
    u32 field17c;
    u32 field180;
    u32 field184;
    u32 field188;
    u32 field18c;
    u32 field190;
    u32 field194;
    u32 field198;
    u32 field19c;
    u32 field1a0;
    u32 field1a4;
    u32 field1a8;
    u32 field1ac;
    u32 field1b0;
    u32 field1b4;
    u32 field1b8;
    u32 field1bc;
    u32 field1c0;
    u32 field1c4;
    u32 field1c8;
    u32 field1cc;
    u32 field1d0;
    u32 field1d4;
    u32 field1d8;
    u32 field1dc;
    u32 field1e0;
    u32 field1e4;
    u32 field1e8;
    u32 field1ec;
    u32 field1f0;
    u32 field1f4;
    u32 field1f8;
    u32 field1fc;
    u32 field200;
    u32 field204;
    u32 field208;
    u32 field20c;
    u32 field210;
    u32 field214;
    u32 field218;
    u32 field21c;
    u32 field220;
    u32 field224;
    u32 field228;
    u32 field22c;
    u32 field230;
    u32 field234;
    u32 field238;
    u32 field23c;
    u32 field240;
    u32 field244;
    u32 field248;
    u32 field24c;
    u32 field250;
    u32 field254;
    u32 field258;
    u32 field25c;
    u32 field260;
    u32 field264;
    u32 field268;
    u32 field26c;
    u32 field270;
    u32 field274;
    u32 field278;
    u32 field27c;
    u32 field280;
    u32 field284;
    u32 field288;
    u32 field28c;
    u32 field290;
    u32 field294;
    u32 field298;
    u32 field29c;
    u32 field2a0;
    u32 field2a4;
    u32 field2a8;
    u32 field2ac;
    u32 field2b0;
    u32 field2b4;
    u32 field2b8;
    u32 field2bc;
    u32 field2c0;
    u32 field2c4;
    u32 field2c8;
    u32 field2cc;
    u32 field2d0;
    u32 field2d4;
    u32 field2d8;
    u32 field2dc;
    u32 field2e0;
    u32 field2e4;
    u32 field2e8;
    u32 field2ec;
    u32 field2f0;
    u32 field2f4;
    u32 field2f8;
    u32 field2fc;
    u32 field300;
    u32 field304;
    u32 field308;
    u32 field30c;
    u32 field310;
    u32 field314;
    u32 field318;
    u32 field31c;
    u32 field320;
    u32 field324;
    u32 field328;
    u32 field32c;
    u32 field330;
    u32 field334;
    u32 field338;
    u32 field33c;
    u32 field340;
    u32 field344;
    u32 field348;
    u32 field34c;
    u32 field350;
    u32 field354;
    u32 field358;
    u32 field35c;
    u32 field360;
    u32 field364;
    u32 field368;
    u32 field36c;
    u32 field370;
    u32 field374;
    u32 field378;
    u32 field37c;
    u32 field380;
    u32 field384;
    u32 field388;
    u32 field38c;
    u32 field390;
    u32 field394;
    u32 field398;
    u32 field39c;
    u32 field3a0;
    u32 field3a4;
    u32 field3a8;
    u32 field3ac;
    u32 field3b0;
    u32 field3b4;
    u32 field3b8;
    u32 field3bc;
    u32 field3c0;
    u32 field3c4;
    u32 field3c8;
    u32 field3cc;
    u32 field3d0;
    u32 field3d4;
    u32 field3d8;
    u32 field3dc;
    u32 field3e0;
    u32 field3e4;
    u32 field3e8;
    u32 field3ec;
    u32 field3f0;
    u32 field3f4;
    u32 field3f8;
    u32 field3fc;
    u32 field400;
    u32 field404;
    u32 field408;
    u32 field40c;
    u32 field410;
    u32 field414;
    u32 field418;
    u32 field41c;
    u32 field420;
    u32 field424;
    u32 field428;
    u32 field42c;
    u32 field430;
    u32 field434;
    u32 CostumeID;
    u32 ColorID;
    u32 field440;
    u32 field444;
    u32 field448;
    u32 field44c;
} CSS_INFO;