//BLUEFIRE1337 PALADINS SDK - UPDATED 2021-08-19
#pragma once

constexpr auto ENGINE = 0x371E880; // Paladins.exe + ENGINE -> UEngine 

constexpr auto LOCALPLAYER = 0x6D8; // UEngine -> ULocalPlayer
constexpr auto CONTROLLER = 0x68; // ULocalPlayer -> APlayerController

constexpr auto ROTATION = 0x008C; // APlayerController -> FRotator
constexpr auto WORLD_INFO = 0x0120; // APlayerController -> AWorldInfo

constexpr auto ACKNOWLEDGEDPAWN = 0x0498; // APlayerController -> acknowledgedPawn | APawn

constexpr auto PLAYER_FOV_MULTIPLIER = 0x04CC; // APlayerController -> FOVMultiplier, aka LODDistanceFactor | float
constexpr auto CAMERA = 0x0478; // APlayerController -> ACamera

constexpr auto REAL_LOCATION = 0x0494; // ACamera -> FVector
constexpr auto DEAFULT_FOV = 0x0290; // ACamera -> float
// FOV = DEAFULT_FOV * PLAYER_FOV_MULTIPLIER

constexpr auto PAWN_LIST = 0x05B4; // AWorldInfo -> pawnList
constexpr auto TIMESECONDS = 0x04EC; // AWorldInfo -> float

constexpr auto TEAM = 0x4DC; // APlayerReplicationInfo -> Team 
constexpr auto TEAMINDEX = 0x298; // Team -> int

constexpr auto AMMO_COUNT = 0x4A4; // ATgDevice -> int
constexpr auto AMMO_MAX_COUNT = 0x5F0; // ATgDevice -> int

constexpr auto GLOW = 0x674; // acknowledgedPawn -> glow
constexpr auto THIRDPERSON = 0x0624; // acknowledgedPawn -> write float
constexpr auto WEAPON = 0x04E4; // APawn -> ATgDevice
constexpr auto BASE_EYE_HEIGHT = 0x03A4; // APawn -> float
constexpr auto HEALTH = 0xA90; // APawn -> float
constexpr auto GET_HEALTH = 0x3C4; // APawn -> float
constexpr auto MAX_HEALTH = 0x111C; // APawn -> float
constexpr auto LOCATION = 0x0080; // APawn -> FVector
constexpr auto VELOCITY = 0x0190; // APawn -> FVector
constexpr auto PLAYER_REPLICATION_INFO = 0x0440; // APawn -> APlayerReplicationInfo
constexpr auto NEXT_PAWN = 0x02AC; // APawn -> next APawn
constexpr auto MESH = 0x048C; // APawn -> USkeletalMeshComponent

constexpr auto BOUNDS = 0x00A0; // USkeletalMeshComponent -> FBoxSphereBounds
constexpr auto LAST_RENDER_TIME = 0x0244; // USkeletalMeshComponent -> float

constexpr auto PLAYER_NAME = 0x0290; // APlayerReplicationInfo -> FString
constexpr auto RECOIL_SETTINGS = 0x0960; // ATgDevice -> FRecoilSettings
constexpr auto ACCURACY_SETTINGS = 0x08C0; // ATgDevice -> FAccuracySettings

constexpr auto CURRENT_PROJECTILES = 0x0610; // ATgDevice -> TArray<ATgProjectile>
constexpr auto PROJECTILE_SPEED = 0x0280; // ATgProjectile -> float