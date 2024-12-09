// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdio.h>
#include "config.h"
#include <random> 

auto CreateConsole = [](const char* name) {
    FILE* ConsoleIO;
    if (!AllocConsole())
        return;

    freopen_s(&ConsoleIO, "CONIN$", "r", stdin);
    freopen_s(&ConsoleIO, "CONOUT$", "w", stderr);
    freopen_s(&ConsoleIO, "CONOUT$", "w", stdout);

    SetConsoleTitleA(name);
};

bool DEBUG = 0;

// DNF v1.0.0 = 0x1422ef2e0
void* FindFileInPakFiles = sigScan(
    "\x48\x89\x5C\x24\x00\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x6C\x24\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x45\x17\x4C\x8B\xE2\x49\x8B\xD8\x48\x8D\x91\x00\x00\x00\x00\x4C\x8B\xF1\x49\x8B\xCC\x41\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x49\x8B\xD4\x48\x8D\x4D\xAF\xE8\x00\x00\x00\x00\x41\x80\xBE\x00\x00\x00\x00\x00\x0F\x84\x00\x00\x00\x00\x8B\x75\xB7\x33\xFF\x44\x8D\x46\xFF\x85\xF6\x75\x03\x44\x8B\xC7",
    "xxxx?xxxxxxxxxxxxxxx?xxx????xxx????xxxxxxxxxxxxxxxx????xxxxxxxx????x????xxxx????xxxxxxxx????xxx?????xx????xxxxxxxxxxxxxxxx");

// DNF v1.0.0 = 0x1422f3e30
void* IsNonPakFilenameAllowed = sigScan(
    "\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x56\x57\x41\x56\x48\x83\xEC\x30\x48\x8B\x00\x45\x33\xC0\x48\x8D\x4C\x24\x00\x00\x8B\xF2\xE8\x00\x00\x00\x00\x48\x8D\x2D\x00\x00\x00\x00\x83\x78\x08\x00\x74\x05\x48\x8B\x10\xEB\x03",
    "xxxx?xxxx?xxxxxxxxxx?xxxxxxx??xxx????xxx????xxxxxxxxxxx");

// v1.24 = 0x14113809b
// v1.25 = 0x141126D8B
// v1.33 = 0x14117166c
// v1.33 = 0x140b123df
void* GetPlayerInputStage = sigScan(
    "\x48\x8D\x05\x2A\x2A\x2A\x2A\x4C\x89\x49\x2A\x4C\x03\xC0",
    "xxx????xxx?xxx");

// v1.24 = 0x140d3b220
// v1.25 = 0x140D25860
// v1.26 = 0x140d27840
// v1.29 = 0x140d30e90
// v1.26 func call = 0x140d2a162
// v1.29 func call = 0x140d33489
void* LoadCharacterCSS_sig = sigScan(
    "\xE8\x2A\x2A\x2A\x2A\x45\x85\xED\xC7\x44\x24\x2A\x00\x00\x00\x00",
    "x????xxxxxx?xxxx");

// v1.24 = 0x140e2da40
// v1.25 = 0x140E1A750
void* AssetPreloadFunctionBattle = sigScan(
    "\x48\x89\x5C\x24\x2A\x48\x89\x4C\x24\x2A\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x6C\x24\x2A\x48\x81\xEC\xE0\x00\x00\x00\x4C\x8B\xE2",
    "xxxx?xxxx?xxxxxxxxxxxxxxx?xxxxxxxxxx");

// v1.24 = 0x14103F930
// v1.25 = 0x14102E160
// v1.25 func call = 0x141028c94
void* AssetSpawnPlayerBattle_Sig = sigScan(
    "\xE8\x2A\x2A\x2A\x2A\x48\x8B\x06\xB2\x01\x48\x8B\xCE\xC7\x86\x2A\x2A\x2A\x2A\x02\x00\x00\x00",
    "x????xxxxxxxxxx????xxxx");

// v1.29 = 0x14151a610
void* KismetExecuteMessage_Sig = sigScan(
    "\x48\x89\x5C\x24\x2A\x57\x48\x83\xEC\x30\x0F\xB6\xDA",
    "xxxx?xxxxxxxx");

// v1.29 = 0x140fec9cd
void* CharaIDTableAccess = sigScan(
    "\x48\x8D\x35\x2A\x2A\x2A\x2A\x33\xD2\x48\x8B\xD9",
    "xxx????xxxxx");

// v1.29 = 0x140bc1e90
void* RoundResult_Sig = sigScan(
    "\x48\x89\x5C\x24\x2A\x48\x89\x6C\x24\x2A\x48\x89\x74\x24\x2A\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x83\xEC\x20\x48\x8B\x05\x2A\x2A\x2A\x2A\x33\xDB",
    "xxxx?xxxx?xxxx?xxxxxxxxxxxxxxxx????xx");

uint64_t CurrentBaseAddress = GetCurrentBaseAddress();
uint64_t baseAddressGhidra = 0x140000000;

UE4PlayerInput* PlayerInput1;
UE4PlayerInput* PlayerInput2;

GlobalCharTables* CharaTable;

int Player1ColorID = -1;
int Player2ColorID = -1;
int Player1CostumeID = 1;
int Player2CostumeID = 1;
int Player1CharID = -1;
int Player2CharID = -1;
bool HasPlayer1Costume = false;
bool HasPlayer2Costume = false;
bool OnlineP1Fix = false;

int randomIntBetween(int min, int max) //range : [min, max]
{
    std::random_device rd; // https://stackoverflow.com/questions/10710840/whats-the-standard-way-for-getting-uniformly-distributed-random-integers-in-c
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(engine);
}

int Player1RandCos = randomIntBetween(0, 4);
int Player2RandCos = randomIntBetween(0, 4);

bool FileExists(LPCWSTR path)
{
    DWORD dwAttrib = GetFileAttributesW(path);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

bool isCharStringMatchCharID(wchar_t* Name, int PlayerSide) // online fix, lol
{
    int charaID = -1;
    bool result = false;

    if (PlayerSide == 1) charaID = Player1CharID;
    else charaID = Player2CharID;

    // if (!Name) return false;

    if (DEBUG) printf("isCharStringMatchCharID checking data for chara %02d\n", charaID);

    for (int i = 0; i < 0x22; i++)
    {
        if (CharaTable->CharacterTables[i].charID == charaID)
        {
            if (wcsstr(Name, CharaTable->CharacterTables[i].Name))
            {
                result = true;
                if (DEBUG) printf("isCharStringMatchCharID success! Matched %02d to %S\n", charaID, Name);
            }
            else
            {
                result = false;
                if (DEBUG) printf("isCharStringMatchCharID failure. Got %02d which does not match %S\n", charaID, Name);
            }
        }
    }

    return result;
}

HOOK(void*, __fastcall, hook_FindFileInPakFiles, FindFileInPakFiles,
    void* PakFile, 
    wchar_t* Filename,
    void** FileEntry
)
{
    const TCHAR* TargetFile = *(TCHAR**)Filename;
    
    if ( wcsstr(TargetFile, L"../../../RED") != NULL && FileExists(TargetFile) && config::enableLooseFileLoad )
    {
        //printf("Redirected File: %S\r\n", TargetFile);
        return 0; // file exists loosely, return false so the game thinks that it doesn't exist in the .pak
    }

    if (config::enableConsole && config::enableFileAccessLog && wcsstr(TargetFile, L"../../../RED/")) //only log files accessed in pak
    {
        printf("FindFileInPakFiles: %S\r\n", TargetFile);
    }

    return orig_hook_FindFileInPakFiles(PakFile, Filename, FileEntry);
}

HOOK(uint64_t, __fastcall, hook_IsNonPakFilenameAllowed, IsNonPakFilenameAllowed,
    void* thisptr,
    void* Filename
)
{
    return 1;
}

HOOK(void, __fastcall, hook_LoadCharacterCSS, GetAddressFromFuncCall(u64(LoadCharacterCSS_sig)),
    u64 a1, u32 charID, u32 ColorID, u32 CostumeID, u32 a5, u8 PlayerID)
{
    // if (DEBUG) printf("CSS Function: a1 0x%llx -- a2 %d -- a3 %d -- a4 %d -- a5 %d -- a6 %d\n", a1, charID, ColorID, CostumeID, a5, PlayerID);
    if ( a1 == 0 ) return orig_hook_LoadCharacterCSS(a1, charID, ColorID, CostumeID, a5, PlayerID);

    if (PlayerID == 0) // check player 1
    {
        Player1ColorID = ColorID;
        Player1CharID = charID;

        if (PlayerInput1->L1 == 1)
        {
            Player1CostumeID = 2;
            if (DEBUG) printf("P1 picked Costume %d; char id %d color %d\n", Player1CostumeID, charID, ColorID);
        }
        else if (PlayerInput1->L2 == 1)
        {
            Player1CostumeID = 3;
            if (DEBUG) printf("P1 picked Costume %d; char id %d color %d\n", Player1CostumeID, charID, ColorID);
        }
        else if (PlayerInput1->R1 == 1)
        {
            Player1CostumeID = 4;
            if (DEBUG) printf("P1 picked Costume %d; char id %d color %d\n", Player1CostumeID, charID, ColorID);
        }
        else if (PlayerInput1->R2 == 1)
        {
            Player1CostumeID = 5;
            if (DEBUG) printf("P1 picked Costume %d; char id %d color %d\n", Player1CostumeID, charID, ColorID);
        }
        else if (PlayerInput1->L3 == 1 || PlayerInput1->Circle == 1)
        {
            Player1CostumeID = 0;
            HasPlayer1Costume = false;
            if (DEBUG) printf("P1 reverted to Costume 1\n");
        }

        if (Player1CostumeID > 1)
        {
            HasPlayer1Costume = true;
        }
        else
        {
            HasPlayer1Costume = false;
        }

        if (HasPlayer1Costume)
        {
            CostumeID = Player1CostumeID - 1;
        }
    }
    else if (PlayerID == 1) // check player 2
    {
        if (PlayerInput2->L1 == 1 || PlayerInput1->RightStickLeft)
        {
            Player2CostumeID = 2;
            if (DEBUG) printf("P2 picked Costume %d; char id %d color %d\n", Player2CostumeID, charID, ColorID);
        }
        else if (PlayerInput2->L2 == 1 || PlayerInput1->RightStickRight)
        {
            Player2CostumeID = 3;
            if (DEBUG) printf("P2 picked Costume %d; char id %d color %d\n", Player2CostumeID, charID, ColorID);
        }
        else if (PlayerInput2->R1 == 1 || PlayerInput1->RightStickUp)
        {
            Player2CostumeID = 4;
            if (DEBUG) printf("P2 picked Costume %d; char id %d color %d\n", Player2CostumeID, charID, ColorID);
        }
        else if (PlayerInput2->R2 == 1 || PlayerInput1->RightStickDown)
        {
            Player2CostumeID = 5;
            if (DEBUG) printf("P2 picked Costume %d; char id %d color %d\n", Player2CostumeID, charID, ColorID);
        }
        else if (PlayerInput2->L3 == 1 || PlayerInput2->Circle == 1 || PlayerInput1->R3)
        {
            Player2CostumeID = 0;
            HasPlayer2Costume = false;
            if (DEBUG) printf("P2 reverted to Costume 1\n");
        }

        if (Player2CostumeID > 1)
        {
            HasPlayer2Costume = true;
        }
        else
        {
            HasPlayer2Costume = false;
            Player2CharID = -1;
        }

        if (HasPlayer2Costume)
        {
            Player2ColorID = ColorID;
            CostumeID = Player2CostumeID - 1;
            Player2CharID = charID;
        }
    }

    return orig_hook_LoadCharacterCSS(a1, charID, ColorID, CostumeID, a5, PlayerID);
}

HOOK(u64, __fastcall, hook_AssetPreloadFunctionBattle, AssetPreloadFunctionBattle,
    FSpawnPlayerInfo* a1, u64 a2)
{
    if (a1->SideID == SIDE_1P && a1->MemberID == 0)
    {
        if (DEBUG) printf("AssetPreloadFunctionBattle: P1 Chara %S with color %d\n", a1->CharaID.Name, a1->ColorID);

        if (HasPlayer1Costume)
        {
            if (isCharStringMatchCharID(a1->CharaID.Name, 1) && a1->ColorID == Player1ColorID)
            {
                a1->CostumeID = Player1CostumeID - 1;
                printf("AssetPreloadFunctionBattle: Applied Costume %d to P1\n", a1->CostumeID + 1);
            }
            else
            {
                OnlineP1Fix = true;
                printf("AssetPreloadFunctionBattle: P1 character mismatch, expected char id %d color %d, received %S and %d instead\n", Player1CharID, Player1ColorID, a1->CharaID.Name, a1->ColorID);
            }
        }
        else
        {
            a1->CostumeID = 0;

            if (config::RandomCostumes)
            {
                printf("P1 Random Costume is %02d\n", Player1RandCos + 1);
                a1->CostumeID = Player1RandCos;
            }
        }

        // if (Player1CostumeID != Player2CostumeID && (Player1CostumeID > 1 || Player2CostumeID > 1)) a1->ColorID = Player1ColorID; // same color diff costume fix
    }
    else if (a1->SideID == SIDE_2P && a1->MemberID == 0)
    {
        if (DEBUG) printf("AssetPreloadFunctionBattle: P2 Chara %S with color %d\n", a1->CharaID.Name, a1->ColorID);

        if (HasPlayer2Costume)
        {
            a1->CostumeID = Player2CostumeID - 1;
            printf("AssetPreloadFunctionBattle: Applied Costume %d to P2\n", a1->CostumeID + 1);
        }
        else if (OnlineP1Fix && isCharStringMatchCharID(a1->CharaID.Name, 1) && a1->ColorID == Player1ColorID) // online fix
        {
            a1->CostumeID = Player1CostumeID - 1;
            printf("AssetPreloadFunctionBattle: Applied Online P2 Costume Fix\n");
        }
        else
        {
            a1->CostumeID = 0;

            if (config::RandomCostumes)
            {
                printf("P2 Random Costume is %02d\n", Player2RandCos + 1);
                a1->CostumeID = Player2RandCos;
            }
        }

        // if (Player1CostumeID != Player2CostumeID && (Player1CostumeID > 1 || Player2CostumeID > 1)) a1->ColorID = Player2ColorID; // same color diff costume fix
    }
    //u64 result = orig_hook_AssetPreloadFunctionBattle(a1, a2);
    return orig_hook_AssetPreloadFunctionBattle(a1, a2);
}

HOOK(void, __fastcall, hook_AssetSpawnPlayerBattle, GetAddressFromFuncCall(u64(AssetSpawnPlayerBattle_Sig)),
    u64 a1,
    u64 a2,
    FSpawnPlayerInfo* a3
)
{
    if (a3->SideID == SIDE_1P && a3->MemberID == 0)
    {
        //if (Player1CostumeID != Player2CostumeID && (Player1CostumeID > 1 || Player2CostumeID > 1)) a3->ColorID = Player1ColorID;

        if (HasPlayer1Costume && !OnlineP1Fix)
        {
            a3->CostumeID = Player1CostumeID - 1;
            //HasPlayer1Costume = false;
            if (DEBUG) printf("AssetLoadFunctionBattle: Applied Costume %d to P1\n", a3->CostumeID + 1);
        }
        else
        {
            a3->CostumeID = 0;

            if (config::RandomCostumes)
            {
                a3->CostumeID = Player1RandCos;
            }
        }

        printf("P1 Loading with Costume %d \n", a3->CostumeID + 1);
    }
    else if (a3->SideID == SIDE_2P && a3->MemberID == 0)
    {
        //if (Player1CostumeID != Player2CostumeID && (Player1CostumeID > 1 || Player2CostumeID > 1)) a3->ColorID = Player2ColorID;

        if (OnlineP1Fix) // online fix
        {
            a3->CostumeID = Player1CostumeID - 1;
            OnlineP1Fix = false;
            if (DEBUG) printf("AssetLoadFunctionBattle: Applied Costume %d to P2\n", a3->CostumeID + 1);
            printf("Applied Online P2 Costume Fix\n");
        }
        else if (HasPlayer2Costume)
        {
            a3->CostumeID = Player2CostumeID - 1;
            if (DEBUG) printf("AssetLoadFunctionBattle: Applied Costume %d to P2\n", a3->CostumeID + 1);
            //HasPlayer2Costume = false;
        }
        else
        {
            a3->CostumeID = 0;

            if (config::RandomCostumes)
            {
                a3->CostumeID = Player2RandCos;
            }

            Player1RandCos = randomIntBetween(0, 4);
            Player2RandCos = randomIntBetween(0, 4); // re-randomize random costumes
        }

        printf("P2 Loading with Costume %d \n", a3->CostumeID + 1);

        //Player1CostumeID = 1;
        //Player2CostumeID = 1;
    }

    return orig_hook_AssetSpawnPlayerBattle(a1, a2, a3);
}

HOOK(void, __stdcall, hook_KismetExecuteMessage, KismetExecuteMessage_Sig, u64* Message, u8 Verbosity)
{
    printf("[Script Msg] %S\r\n", Message);
    return orig_hook_KismetExecuteMessage(Message, Verbosity);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        config::init(hModule);

        if ( config::enableConsole ) // open console output
        {
            AllocConsole();
            AttachConsole(GetCurrentProcessId());
            freopen("CON", "w", stdout);

            CreateConsole("GGST Costumes Patch");
            std::cout << "Console Alloc Success" << std::endl;

            //printf("Current base addres is 0x%p\n", CurrentBaseAddress);
        }

        if (GetPlayerInputStage && config::enableCostumes)
        {
            if (DEBUG) printf("Signature for GetPlayerInputStage fount at 0x%p\n", ((u64)GetPlayerInputStage - CurrentBaseAddress) + baseAddressGhidra);
            printf("Player Input Address at 0x%p\n", GetAddressFromGlobalRef((u64)GetPlayerInputStage));
            PlayerInput1 = (UE4PlayerInput*)GetAddressFromGlobalRef((u64)GetPlayerInputStage);
            PlayerInput2 = (UE4PlayerInput*)(GetAddressFromGlobalRef((u64)GetPlayerInputStage) + 0x2C);
        }
        else
        {
            if (!GetPlayerInputStage) printf("Signature GetPlayerInputStage broken!\n");
        }

        if ( FindFileInPakFiles && ( config::enableFileAccessLog || config::enableLooseFileLoad))
        {
            if (DEBUG) printf("Signature for FindFileInPakFiles fount at 0x%p\n", ((u64)FindFileInPakFiles - CurrentBaseAddress) + baseAddressGhidra);
            INSTALL_HOOK(hook_FindFileInPakFiles);
        }
        else
        {
            if (!FindFileInPakFiles) printf("Signature for FindFileInPakFiles broken!\n");
        }

        if ( IsNonPakFilenameAllowed && config::enableLooseFileLoad )
        {
            if (DEBUG) printf("Signature for IsNonPakFilenameAllowed fount at 0x%p\n", ((u64)IsNonPakFilenameAllowed - CurrentBaseAddress) + baseAddressGhidra);
            INSTALL_HOOK(hook_IsNonPakFilenameAllowed);
        }
        else
        {
            if (!IsNonPakFilenameAllowed) printf("Signature for IsNonPakFilenameAllowed broken!\n");
        }

        if (AssetPreloadFunctionBattle && config::enableCostumes)
        {
            if (DEBUG) printf("Signature for AssetPreloadFunctionBattle fount at 0x%p\n", ((u64)AssetPreloadFunctionBattle - CurrentBaseAddress) + baseAddressGhidra);
            INSTALL_HOOK(hook_AssetPreloadFunctionBattle);
        }
        else
        {
            if (!AssetPreloadFunctionBattle) printf("Signature for AssetPreloadFunctionBattle broken!\n");
        }

        if (LoadCharacterCSS_sig && config::enableCostumes)
        {
            if (DEBUG) printf("Signature for LoadCharacterCSS fount at 0x%p, real address at 0x%p\n", ((u64)LoadCharacterCSS_sig - CurrentBaseAddress) + baseAddressGhidra, (GetAddressFromFuncCall(u64(LoadCharacterCSS_sig)) - CurrentBaseAddress) + baseAddressGhidra);
            if (GetPlayerInputStage) INSTALL_HOOK(hook_LoadCharacterCSS);
        }
        else
        {
            if (!LoadCharacterCSS_sig) printf("Signature for LoadCharacterCSS_sig broken!\n");
        }

        if (AssetSpawnPlayerBattle_Sig && config::enableCostumes)
        {
            if (DEBUG) printf("Signature for AssetSpawnPlayerBattle_Sig fount at 0x%p, real address at 0x%p\n", ((u64)AssetSpawnPlayerBattle_Sig - CurrentBaseAddress) + baseAddressGhidra, (GetAddressFromFuncCall(u64(AssetSpawnPlayerBattle_Sig)) - CurrentBaseAddress) + baseAddressGhidra);
            INSTALL_HOOK(hook_AssetSpawnPlayerBattle);
        }
        else
        {
            if (!AssetSpawnPlayerBattle_Sig) printf("Signature for AssetSpawnPlayerBattle_Sig broken!\n");
        }

        if (KismetExecuteMessage_Sig && config::PrintBlueprintErrors)
        {
            if (DEBUG) printf("Signature for KismetExecuteMessage fount at 0x%p, real address at 0x%p\n", ((u64)KismetExecuteMessage_Sig - CurrentBaseAddress) + baseAddressGhidra, ((u64)KismetExecuteMessage_Sig - CurrentBaseAddress) + baseAddressGhidra);
            INSTALL_HOOK(hook_KismetExecuteMessage);
        }
        else
        {
            if (!KismetExecuteMessage_Sig) printf("Signature for KismetExecuteMessage_Sig broken!\n");
        }

        if (CharaIDTableAccess && config::enableCostumes)
        {
            if (DEBUG) printf("Signature for CharaIDTableAccess fount at 0x%p, real address at 0x%p\n", ((u64)CharaIDTableAccess - CurrentBaseAddress) + baseAddressGhidra, (GetAddressFromGlobalRef(u64(CharaIDTableAccess)) - CurrentBaseAddress) + baseAddressGhidra);
            CharaTable = (GlobalCharTables*)GetAddressFromGlobalRef(u64(CharaIDTableAccess));
        }
        else
        {
            printf("Signature for CharaIDTableAccess broken!\n");
        }


        config::init(hModule);

        return TRUE;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}