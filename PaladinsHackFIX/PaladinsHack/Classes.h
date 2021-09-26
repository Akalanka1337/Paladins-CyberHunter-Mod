// MADE BY BLUEFIRE1337

#pragma once
#include <cstdint>
#include "Offsets.h"
#include "GameClasses.h"
#include "Mhyprot/baseadress.h"

template<class T>
class TArray
{
	//friend struct FString;
public:
	int Length() const
	{
		return m_nCount;
	}

	bool IsValid() const
	{
		if(m_nCount > m_nMax)
			return false;
		if(!m_Data)
			return false;
		return true;
	}

	uint64_t GetAddress() const
	{
		return m_Data;
	}

	T GetById(int i)
	{
		return read<T>(m_Data + i * 8);
	}

protected:
	uint64_t m_Data;
	uint32_t m_nCount;
	uint32_t m_nMax;
};

struct FString : private TArray<wchar_t>
{
	std::wstring ToWString() const
	{
		wchar_t* buffer = new wchar_t[m_nCount];
		read_array(m_Data, buffer, m_nCount);
		std::wstring ws(buffer);
		delete[] buffer;

		return ws;
	}

	std::string ToString() const
	{
		std::wstring ws = ToWString();
		std::string str(ws.begin(), ws.end());

		return str;
	}
};

class ATgProjectile {
public:
	inline float GetSpeed() {
		return read<float>(data + PROJECTILE_SPEED);
	}
	uint64_t data;
};

class USkeletalMeshComponent {
public:
	inline FBoxSphereBounds GetBounds() {
		return read<FBoxSphereBounds>(data + BOUNDS);
	}

	inline float GetLastRenderTime() {
		return read<float>(data + LAST_RENDER_TIME);
	}

	inline bool IsVisible(float timeSeconds) {
		float lastRenderTime = GetLastRenderTime();
		return (lastRenderTime > timeSeconds - 0.05f);
	}

	uint64_t data;
};

class ATeamInfo {
public:
	inline int GetTeamIndex() {
		return read<int>(data + TEAMINDEX);
	}

	uint64_t data;
};

class APlayerReplicationInfo {
public:
	ATeamInfo GetTeamInfo() {
		return read<ATeamInfo>(data + TEAM);
	}

	FString GetName() {
		return read<FString>(data + PLAYER_NAME);
	}

	uint64_t data;
};

struct FRecoilSettings {
	int                                                bUsesRecoil;                                              // 0x0000(0x0004)
	float                                              fRecoilReductionPerSec;                                   // 0x0004(0x0004)
	float                                              fRecoilCenterDelay;                                       // 0x0008(0x0004)
	float                                              fRecoilSmoothRate;                                        // 0x000C(0x0004) 
};

struct FAccuracySettings
{
	int                                                bUsesAdvancedAccuracy;                                    // 0x0000(0x0004)
	float                                              fMaxAccuracy;                                             // 0x0004(0x0004)
	float                                              fMinAccuracy;                                             // 0x0008(0x0004)
	float                                              fAccuracyLossPerShot;                                     // 0x000C(0x0004)
	float                                              fAccuracyGainPerSec;                                      // 0x0010(0x0004)
	float                                              fAccuracyGainDelay;                                       // 0x0014(0x0004)
	int                                                nNumFreeShots;                                            // 0x0018(0x0004)
};

static FRecoilSettings oldRecoilSettings;
static bool hasRecoil = true;
static FAccuracySettings oldAccuracySettings;
static bool hasSpread = true;

class ATgDevice {
public:
	inline FRecoilSettings GetRecoil() {
		return read<FRecoilSettings>(data + RECOIL_SETTINGS);
	}

	inline bool SetRecoil(FRecoilSettings settings) {
		return write(data + RECOIL_SETTINGS, settings);
	}

	inline FAccuracySettings GetAccuracy() {
		return read<FAccuracySettings>(data + ACCURACY_SETTINGS);
	}

	inline bool SetAccuracy(FAccuracySettings settings) {
		return write(data + ACCURACY_SETTINGS, settings);
	}

	inline void NoRecoil(bool toggle = true) {
		if(toggle) {
			auto recoil = GetRecoil();
			if(recoil.bUsesRecoil) {
				oldRecoilSettings = recoil;
			}
			recoil.bUsesRecoil = false;
			recoil.fRecoilCenterDelay = 0;
			recoil.fRecoilReductionPerSec = 0;
			recoil.fRecoilSmoothRate = 0;
			hasRecoil = false;
			SetRecoil(recoil);
		}
		else {
			if(!hasRecoil) {
				hasRecoil = true;
				SetRecoil(oldRecoilSettings);
			}
		}
	}


	inline void NoSpread(bool toggle) {
		if(toggle) {
			auto accuracy = GetAccuracy();
			accuracy.fAccuracyGainPerSec = 0;
			accuracy.fMaxAccuracy = 1;
			accuracy.fMinAccuracy = 1;
			hasSpread = false;
			SetAccuracy(accuracy);
		}
		else {
			if(!hasSpread) {
				hasSpread = true;
				SetAccuracy(oldAccuracySettings);
			}
		}
	}


	inline int GetAmmoCount() {
		return read<int>(data + AMMO_COUNT);
	}

	inline TArray<ATgProjectile> GetProjectiles() {
		return read<TArray<ATgProjectile>>(data + CURRENT_PROJECTILES);
	}

	inline int GetMaxAmmoCount() {
		return read<int>(data + AMMO_MAX_COUNT);
	}

	inline void SetPerspective(bool thirdPerson) {
		write<float>(data + THIRDPERSON, thirdPerson ? 1.f : 0.f); // THIS SETS THE DURATION OF THE PERSPECIVE IN SEC
	}

	uint64_t data;
};

class APawn {
public:
	inline ATgDevice GetWeapon() {
		return read<ATgDevice>(data + WEAPON);
	}

	inline int GetHealth() {
		return read<int>(data + GET_HEALTH);
	}

	inline int GetMaxHealth() {
		return (int)read<float>(data + MAX_HEALTH);
	}

	inline bool SetHealth(float hp) {
		return write<float>(data + HEALTH, hp);
	}

	inline int SetMaxHealth(float hp) {
		return write<float>(data + MAX_HEALTH, hp);
	}

	inline FVector GetLocation() {
		return read<FVector>(data + LOCATION);
	}

	inline FRotator GetRotation() {
		return read<FRotator>(data + ROTATION);
	}

	inline FVector GetVelocity() {
		return read<FVector>(data + VELOCITY);
	}

	inline APlayerReplicationInfo GetPlayerReplicationInfo() {
		return read<APlayerReplicationInfo>(data + PLAYER_REPLICATION_INFO);
	}

	inline APawn GetNextPawn() {
		return read<APawn>(data + NEXT_PAWN);
	}

	inline float GetEyeHeight() {
		return read<float>(data + BASE_EYE_HEIGHT);
	}

	inline USkeletalMeshComponent GetMesh() {
		return read<USkeletalMeshComponent>(data + MESH);
	}

	inline void SetGlowhack(bool isGlowing) {
		auto offset = data + GLOW;
		auto current = read<unsigned long>(offset);
		if(isGlowing) {
			current |= (1u << 17);
		}
		else {
			current &= ~(1u << 17); // air = 2
		}

		write(offset, current);
	}

	uint64_t data;
};

class ACamera {
public:
	inline float GetDeafultFov() {
		return read<float>(data + DEAFULT_FOV);
	}

	inline FVector GetRealLocation() {
		return read<FVector>(data + REAL_LOCATION);
	}

	uint64_t data;
};

class AWorldInfo {
public:
	inline float GetTimeSeconds() {
		return read<float>(data + TIMESECONDS);
	}

	inline APawn GetPawnList() {
		return read<APawn>(data + PAWN_LIST);
	}

	uint64_t data;
};

class APlayerController {
public:
	inline FRotator GetRotation() {
		return read<FRotator>(data + ROTATION);
	}

	inline void SetRotation(FRotator rotation) {
		write(data + ROTATION, rotation);
	}

	inline float GetFovMultiplier() {
		return read<float>(data + PLAYER_FOV_MULTIPLIER);
	}

	inline APawn GetAcknowledgedPawn() {
		return read<APawn>(data + ACKNOWLEDGEDPAWN);
	}

	inline ACamera GetCamera() {
		return read<ACamera>(data + CAMERA);
	}

	inline AWorldInfo GetWorldInfo() {
		return read<AWorldInfo>(data + WORLD_INFO);
	}

	uint64_t data;
};

class ULocalPlayer {
public:
	inline APlayerController GetController() {
		return read<APlayerController>(data + CONTROLLER);
	}

	uint64_t data;
};

class UEngine {
public:
	inline ULocalPlayer GetLocalPlayer() {
		return read<ULocalPlayer>(read<uint64_t>(data + LOCALPLAYER));
	}

	uint64_t data;
};


UEngine GetUEngine(uint64_t base) {
	return read<UEngine>(base + ENGINE);
}