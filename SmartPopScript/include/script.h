#pragma once

#include "common.h"

typedef UInt16 ScriptCode;

union ScriptVersionType
{
	struct
	{
		Int8 version;
		Int8 padding;
	};
	ScriptCode code;
};;

namespace utils
{
	constexpr ScriptVersionType ScriptVersion = { { .version = 12, .padding = 0 } };

	constexpr int ScriptCodeCount = 4095;
	constexpr int ScriptFieldCount = 512;
	constexpr int ScriptMaxVariableCount = 64;

	constexpr int ScriptNoCommandModifier = 27;
	constexpr int ScriptTokenOffsetModifier = 1000;
	constexpr int ScriptInternalOffsetModifier = 1000;

	constexpr Size ScriptVersionSize = sizeof(ScriptVersionType);
	constexpr Size ScriptCodeSize = sizeof(ScriptCode) * ScriptCodeCount;
	constexpr Size ScriptFieldSize = sizeof(UInt32) + sizeof(Int32);
	constexpr Size ScriptFieldsSize = ScriptFieldSize * ScriptFieldCount;
	constexpr Size ScriptPaddingSize = 264;

	constexpr Size ScriptSize = ScriptVersionSize + ScriptCodeSize + ScriptFieldsSize + ScriptPaddingSize;
}

#define token(_Code) (utils::ScriptTokenOffsetModifier + (_Code))
#define action(_Code) (token(_Code) + utils::ScriptNoCommandModifier)
#define internal(_Code) (utils::ScriptInternalOffsetModifier + (_Code))

enum class ScriptToken : ScriptCode
{
	If = token(0),
	Else = token(1),
	Endif = token(2),
	Begin = token(3),
	End = token(4),
	Every = token(5),
	Do = token(6),
	Set = token(7),
	Increment = token(8),
	Decrement = token(9),
	//ExpStart = token(10),
	//ExpEnd = token(11),
	GreaterThan = token(12),
	LessThan = token(13),
	EqualTo = token(14),
	NotEqualTo = token(15),
	GreaterThanEqualTo = token(16),
	LessThanEqualTo = token(17),
	ScriptEnd = token(19),
	And = token(20),
	Or = token(21),
	On = token(22),
	Off = token(23),
	//ComputerPlayer = token(24),
	Multiply = token(25),
	Divide = token(26),

	ConstructBuilding = action(1),
	FetchWood = action(2),
	EnableShamanGetWilds = action(3),
	HouseAPerson = action(4),
	SendGhosts = action(5),
	BringNewPeopleBack = action(6),
	TrainPeople = action(7),
	PopulateDrumTower = action(8),
	Defend = action(9),
	DefendBase = action(10),
	SpellDefense = action(11),
	Preach = action(12),
	BuildWalls = action(13),
	Sabotage = action(14),
	SpellOffensive = action(15),
	FirewarriorDefend = action(16),
	BuildVehicle = action(17),
	FetchLostPeople = action(18),
	FetchLostVehicle = action(19),
	FetchFarVehicle = action(20),
	AutoAttack = action(21),

	ShamanDefend = action(22),
	FlattenBase = action(23),
	BuildOuterDefences = action(24),
	Spare5 = action(25),
	Spare6 = action(26),
	Spare7 = action(27),
	Spare8 = action(28),
	Spare9 = action(29),
	Spare10 = action(30),
	CountWild = action(31),

	Attack = action(32),
	AttackBlue = action(33),
	AttackRed = action(34),
	AttackYellow = action(35),
	AttackGreen = action(36),
	SpellAttack = action(37),

	ResetBaseMarker = action(38),
	SetBaseMarker = action(39),
	SetBaseRadius = action(40),
	CountPeopleInMarker = action(41),
	SetDrumTowerPos = action(42),

	AttackMarker = action(43),
	AttackBuilding = action(44),
	AttackPerson = action(45),
	ConvertAtMarker = action(46),
	PreachAtMarker = action(47),
	SendGhostPeople = action(48),
	GetSpellsCast = action(49),
	GetNumOneOffSpells = action(50),
	AttackNormal = action(51),
	AttackByBoat = action(52),
	AttackByBalloon = action(53),
	SetAttackVariable = action(54),
	BuildDrumTower = action(55),
	GuardAtMarker = action(56),
	GuardBetweenMarkers = action(57),
	GetHeightAtPos = action(58),
	SendAllPeopleToMarker = action(59),
	GuardNormal = action(60),
	GuardWithGhosts = action(61),
	ResetConvertMarker = action(62),
	SetConvertMarker = action(63),
	SetMarkerEntry = action(64),
	MarkerEntries = action(65),
	ClearGuardingFrom = action(66),
	SetBuildingDirection = action(67),
	TrainPeopleNow = action(68),
	PrayAtHead = action(69),
	PutPersonInDrumTower = action(70),
	IHaveOneShot = action(71),
	SpellType = action(72),
	BuildingType = action(73),
	BoatPatrol = action(74),
	DefendShamen = action(75),
	SendShamenDefendersHome = action(76),
	BoatType = action(77),
	BalloonType = action(78),
	IsBuildingNear = action(79),
	BuildAt = action(80),
	SetSpellEntry = action(81),
	DelayMainDrumTower = action(82),
	BuildMainDrumTower = action(83),
	ZoomTo = action(84),
	DisableUserInputs = action(85),
	EnableUserInputs = action(86),
	OpenDialog = action(87),
	GiveOneShot = action(88),
	ClearStandingPeople = action(89),
	OnlyStandAtMarkers = action(90),
	Blue = action(91),
	Red = action(92),
	Yellow = action(93),
	Green = action(94),
	NavCheck = action(95),
	TargetFirewarriors = action(96),
	DontTargetFirewarriors = action(97),
	TargetBlueShaman = action(98),
	DontTargetBlueShaman = action(99),
	TargetBlueDrumTowers = action(100),
	DontTargetBlueDrumTowers = action(101),
	HasBlueKilledAGhost = action(102),
	CountGuardFires = action(103),
	GetHeadTriggerCount = action(104),
	MoveShamanToMarker = action(105),
	TrackShamanToAngle = action(106),
	TrackShamanExtraBollocks = action(107),
	IsShamanAvailableForAttack = action(108),
	PartialBuildingCount = action(109),
	SendBluePeopleToMarker = action(110),
	GiveManaToPlayer = action(111),
	IsPlayerInWorldView = action(112),
	SetAutoBuild = action(113),
	DeselectAllBluePeople = action(114),
	FlashButton = action(115),
	TurnPanelOn = action(116),
	GivePlayerSpell = action(117),
	HasPlayerBeenInEncyc = action(118),
	IsBlueShamanSelected = action(119),
	ClearShamanLeftClick = action(120),
	ClearShamanRightClick = action(121),
	IsShamanIconLeftClick = action(122),
	IsShamanIconRightClick = action(123),
	TriggerThing = action(124),
	TrackToMarker = action(125),
	CameraRotation = action(126),
	StopCameraRotation = action(127),
	CountBlueShapes = action(128),
	CountBlueInHouses = action(129),
	HasHouseInfoBeenShown = action(130),
	ClearHouseInfoFlag = action(131),
	SetAutoHouse = action(132),
	CountBlueWithBuildCommand = action(133),
	DontHouseSpecialists = action(134),
	TargetPlayerDrumTowerAndFirewarrior = action(135),
	RemovePlayerThing = action(136),
	SetReincarnation = action(137),
	ExtraWoodCollection = action(138),
	SetWoodCollectionRadii = action(139),
	GetNumPeopleConverted = action(140),
	GetNumPeopleBeingPreached = action(141),

	TriggerLevelLost = action(142),
	TriggerLevelWon = action(143),

	RemoveHeadAtPos = action(144),
	SetBucketUsage = action(145),
	SetBucketCountForSpell = action(146),
	CreateMsgNarrative = action(147),
	CreateMsgObjective = action(148),
	CreateMsgInformation = action(149),
	CreateMsgInformationZoom = action(150),
	SetMsgZoom = action(151),
	SetMsgTimeout = action(152),
	SetMsgDeleteOnOk = action(153),
	SetMsgReturnOnOk = action(154),
	SetMsgDeleteOnRmbZoom = action(155),
	SetMsgOpenDlgOnRmbZoom = action(156),
	SetCreateReturnMsgOnRmbZoom = action(157),
	SetMsgOpenDlgOnRmbDelete = action(158),
	SetMsgZoomOnRmbOpenDlg = action(159),
	SetMsgAutoOpenDlg = action(160),
	SetSpecialNoBldgPanel = action(161),
	SetMsgOkSaveExitDlg = action(162),
	FixWildInArea = action(163),
	CheckIfPersonPreachedTo = action(164),
	CountAngels = action(165),
	SetNoBlueReinc = action(166),
	IsShamanInArea = action(167),
	ForceTooltip = action(168),
	SetDefenseRadius = action(169),
	MarvellousHouseDead = action(170),
	CallToArms = action(171),
	DeleteSmokeStuff = action(172),
	SetTimerGoing = action(173),
	RemoveTimer = action(174),
	HasTimerReachedZero = action(175),
	StartReincNow = action(176),
	TurnPush = action(177),
	FlybyCreateNew = action(178),
	FlybyStart = action(179),
	FlybyStop = action(180),
	FlybyAllowInterrupt = action(181),
	FlybySetEventPos = action(182),
	FlybySetEventAngle = action(183),
	FlybySetEventZoom = action(184),
	FlybySetEventIntPoint = action(185),
	FlybySetEventTooltip = action(186),
	FlybySetEndTarget = action(187),
	FlybySetMessage = action(188),
	KillTeamInArea = action(189),
	ClearAllMsg = action(190),
	SetMsgId = action(191),
	GetMsgId = action(192),
	KillAllMsgId = action(193),
	GiveUpAndSulk = action(194),
	AutoMessages = action(195),
	IsPrisonOnLevel = action(196)
};

enum class ScriptInternal : ScriptCode
{
	GameTurn = 0,
	MyNumPeople = 1,
	BluePeople = 2,
	RedPeople = 3,
	YellowPeople = 4,
	GreenPeople = 5,
	MyNumKilledByHuman = 6,
	RedKilledByHuman = 7,
	YellowKilledByHuman = 8,
	GreenKilledByHuman = 9,
	WildPeople = 10,
	BlueMana = 11,
	RedMana = 12,
	YellowMana = 13,
	GreenMana = 14,

	AttrExpansion = internal(0),
	AttrPrefSpyTrains = internal(1),
	AttrPrefReligiousTrains = internal(2),
	AttrPrefWarriorTrains = internal(3),
	AttrPrefFirewarriorTrains = internal(4),
	AttrPrefSpyPeople = internal(5),
	AttrPrefReligiousPeople = internal(6),
	AttrPrefWarriorPeople = internal(7),
	AttrPrefFirewarriorPeople = internal(8),
	AttrMaxBuildingsOnGo = internal(9),
	AttrHousePercentage = internal(10),
	AttrAwayBrave = internal(11),
	AttrAwayWarrior = internal(12),
	AttrAwayReligious = internal(13),
	AttrDefenseRadIncr = internal(14),
	AttrMaxDefensiveActions = internal(15),
	AttrAwaySpy = internal(16),
	AttrAwayFirewarrior = internal(17),
	AttrAttackPercentage = internal(18),
	AttrAwayShaman = internal(19),
	AttrPeoplePerBoat = internal(20),
	AttrPeoplePerBalloon = internal(21),
	AttrDontUseBoats = internal(22),
	AttrMaxSpyAttacks = internal(23),
	AttrEnemySpyMaxStand = internal(24),
	AttrMaxAttacks = internal(25),
	AttrEmptyAtWaypoint = internal(26),
	AttrSpyCheckFrequency = internal(27),
	AttrRetreatValue = internal(28),
	AttrBaseUnderAttackRetreat = internal(29),
	AttrRandomBuildSide = internal(30),
	AttrUsePreacherForDefense = internal(31),
	AttrShamenBlast = internal(32),
	AttrMaxTrainAtOnce = internal(33),
	AttrGroupOption = internal(34),
	AttrPrefBoatHuts = internal(35),
	AttrPrefBalloonHuts = internal(36),
	AttrPrefBoatDrivers = internal(37),
	AttrPrefBalloonDrivers = internal(38),
	AttrFightStopDistance = internal(39),
	AttrSpyDiscoverChance = internal(40),
	AttrCountPreachDamage = internal(41),
	AttrDontGroupAtDrumTower = internal(42),
	AttrSpellDelay = internal(43),
	AttrDontDeleteUselessBoatHouse = internal(44),
	AttrBoatHouseBroken = internal(45),
	AttrDontAutoTrainPreachers = internal(46),
	AttrSpare = internal(47),
	
	MyMana = internal(48),

	MySpellBurnCost = internal(49),
	MySpellBlastCost = internal(50),
	MySpellLightningCost = internal(51),
	MySpellTornadoCost = internal(52),
	MySpellSwarmCost = internal(53),
	MySpellInvisibilityCost = internal(54),
	MySpellHypnotismCost = internal(55),
	MySpellFirestormCost = internal(56),
	MySpellGhostArmyCost = internal(57),
	MySpellErosionCost = internal(58),
	MySpellSwampCost = internal(59),
	MySpellLandBridgeCost = internal(60),
	MySpellAngelOfDeadCost = internal(61),
	MySpellEarthquakeCost = internal(62),
	MySpellFlattenCost = internal(63),
	MySpellVolcanoCost = internal(64),
	MySpellArmaggeddonCost = internal(65),

	MyBuildingSmallHut = internal(66),
	MyBuildingMediumHut = internal(67),
	MyBuildingLargeHut = internal(68),
	MyBuildingDrumTower = internal(69),
	MyBuildingTemple = internal(70),
	MyBuildingSpyTrain = internal(71),
	MyBuildingWarriorTrain = internal(72),
	MyBuildingFirewarriorTrain = internal(73),
	MyBuildingReconversion = internal(74),
	MyBuildingWallPiece = internal(75),
	MyBuildingGate = internal(76),
	MyBuildingCurrOeSlot = internal(77),
	MyBuildingBoatHut = internal(78),
	MyBuildingBoatHut2 = internal(79),
	MyBuildingAirshipHut = internal(80),
	MyBuildingAirshipHut2 = internal(81),

	BlueBuildingSmallHut = internal(82),
	BlueBuildingMediumHut = internal(83),
	BlueBuildingLargeHut = internal(84),
	BlueBuildingDrumTower = internal(85),
	BlueBuildingTemple = internal(86),
	BlueBuildingSpyTrain = internal(87),
	BlueBuildingWarriorTrain = internal(88),
	BlueBuildingFirewarriorTrain = internal(89),
	BlueBuildingReconversion = internal(90),
	BlueBuildingWallPiece = internal(91),
	BlueBuildingGate = internal(92),
	BlueBuildingCurrOeSlot = internal(93),
	BlueBuildingBoatHut = internal(94),
	BlueBuildingBoatHut2 = internal(95),
	BlueBuildingAirshipHut = internal(96),
	BlueBuildingAirshipHut2 = internal(97),

	RedBuildingSmallHut = internal(98),
	RedBuildingMediumHut = internal(99),
	RedBuildingLargeHut = internal(100),
	RedBuildingDrumTower = internal(101),
	RedBuildingTemple = internal(102),
	RedBuildingSpyTrain = internal(103),
	RedBuildingWarriorTrain = internal(104),
	RedBuildingFirewarriorTrain = internal(105),
	RedBuildingReconversion = internal(106),
	RedBuildingWallPiece = internal(107),
	RedBuildingGate = internal(108),
	RedBuildingCurrOeSlot = internal(109),
	RedBuildingBoatHut = internal(110),
	RedBuildingBoatHut2 = internal(111),
	RedBuildingAirshipHut = internal(112),
	RedBuildingAirshipHut2 = internal(113),

	YellowBuildingSmallHut = internal(114),
	YellowBuildingMediumHut = internal(115),
	YellowBuildingLargeHut = internal(116),
	YellowBuildingDrumTower = internal(117),
	YellowBuildingTemple = internal(118),
	YellowBuildingSpyTrain = internal(119),
	YellowBuildingWarriorTrain = internal(120),
	YellowBuildingFirewarriorTrain = internal(121),
	YellowBuildingReconversion = internal(122),
	YellowBuildingWallPiece = internal(123),
	YellowBuildingGate = internal(124),
	YellowBuildingCurrOeSlot = internal(125),
	YellowBuildingBoatHut = internal(126),
	YellowBuildingBoatHut2 = internal(127),
	YellowBuildingAirshipHut = internal(128),
	YellowBuildingAirshipHut2 = internal(129),

	GreenBuildingSmallHut = internal(130),
	GreenBuildingMediumHut = internal(131),
	GreenBuildingLargeHut = internal(132),
	GreenBuildingDrumTower = internal(133),
	GreenBuildingTemple = internal(134),
	GreenBuildingSpyTrain = internal(135),
	GreenBuildingWarriorTrain = internal(136),
	GreenBuildingFirewarriorTrain = internal(137),
	GreenBuildingReconversion = internal(138),
	GreenBuildingWallPiece = internal(139),
	GreenBuildingGate = internal(140),
	GreenBuildingCurrOeSlot = internal(141),
	GreenBuildingBoatHut = internal(142),
	GreenBuildingBoatHut2 = internal(143),
	GreenBuildingAirshipHut = internal(144),
	GreenBuildingAirshipHut2 = internal(145),
	
	MyPersonBrave = internal(146),
	MyPersonWarrior = internal(147),
	MyPersonReligious = internal(148),
	MyPersonSpy = internal(149),
	MyPersonFirewarrior = internal(150),
	MyPersonShaman = internal(151),

	BluePersonBrave = internal(152),
	BluePersonWarrior = internal(153),
	BluePersonReligious = internal(154),
	BluePersonSpy = internal(155),
	BluePersonFirewarrior = internal(156),
	BluePersonShaman = internal(157),

	RedPersonBrave = internal(158),
	RedPersonWarrior = internal(159),
	RedPersonReligious = internal(160),
	RedPersonSpy = internal(161),
	RedPersonFirewarrior = internal(162),
	RedPersonShaman = internal(163),

	YellowPersonBrave = internal(164),
	YellowPersonWarrior = internal(165),
	YellowPersonReligious = internal(166),
	YellowPersonSpy = internal(167),
	YellowPersonFirewarrior = internal(168),
	YellowPersonShaman = internal(169),

	GreenPersonBrave = internal(170),
	GreenPersonWarrior = internal(171),
	GreenPersonReligious = internal(172),
	GreenPersonSpy = internal(173),
	GreenPersonFirewarrior = internal(174),
	GreenPersonShaman = internal(175),
	
	BlueKilledByMe = internal(176),
	RedKilledByMe = internal(177),
	YellowKilledByMe = internal(178),
	GreenKilledByMe = internal(179),

	MyNumKilledByBlue = internal(180),
	MyNumKilledByRed = internal(181),
	MyNumKilledByYellow = internal(182),
	MyNumKilledByGreen = internal(183),

	Burn = internal(184),
	Blast = internal(185),
	Lightning = internal(186),
	Tornado = internal(187),
	Swarm = internal(188),
	Invisibility = internal(189),
	Hypnotism = internal(190),
	Firestorm = internal(191),
	GhostArmy = internal(192),
	Erosion = internal(193),
	Swamp = internal(194),
	LandBridge = internal(195),
	AngelOfDead = internal(196),
	Earthquake = internal(197),
	Flatten = internal(198),
	Volcano = internal(199),
	Armaggeddon = internal(200),

	Brave = internal(201),
	Warrior = internal(202),
	Religious = internal(203),
	Spy = internal(204),
	Firewarrior = internal(205),
	Shaman = internal(206),

	SmallHut = internal(207),
	MediumHut = internal(208),
	LargeHut = internal(209),
	DrumTower = internal(210),
	Temple = internal(211),
	SpyTrain = internal(212),
	WarriorTrain = internal(213),
	FirewarriorTrain = internal(214),
	Reconversion = internal(215),
	WallPiece = internal(216),
	Gate = internal(217),
	BoatHut = internal(218),
	BoatHut2 = internal(219),
	AirshipHut = internal(220),
	AirshipHut2 = internal(221),

	NoSpecificPerson = internal(222),
	NoSpecificBuilding = internal(223),
	NoSpecificSpell = internal(224),

	TargetShaman = internal(225),

	MyVehicleBoat = internal(226),
	MyVehicleAirship = internal(227),

	BlueVehicleBoat = internal(228),
	BlueVehicleAirship = internal(229),

	RedVehicleBoat = internal(230),
	RedVehicleAirship = internal(231),

	YellowVehicleBoat = internal(232),
	YellowVehicleAirship = internal(233),

	GreenVehicleBoat = internal(234),
	GreenVehicleAirship = internal(235),
	
	CPFreeEntries = internal(236),
	Random100 = internal(237),

	NumShamenDefenders = internal(238),

	CameraAngle = internal(239),
	CameraX = internal(240),
	CameraZ = internal(241),

	MySpellShieldCost = internal(242),
	Shield = internal(243),
	Convert = internal(244),
	Teleport = internal(245),
	Bloodlust = internal(246),
};

#undef token
#undef action
#undef internal





namespace codes
{
	constexpr ScriptCode as_code(ScriptToken token)
	{
		return static_cast<ScriptCode>(token);
	}

	constexpr ScriptCode as_code(ScriptInternal internal)
	{
		return static_cast<ScriptCode>(internal);
	}

	constexpr ScriptToken as_token(ScriptCode code)
	{
		return static_cast<ScriptToken>(code);
	}

	constexpr ScriptInternal as_internal(ScriptCode code)
	{
		return static_cast<ScriptInternal>(code);
	}

	constexpr bool is_command(ScriptToken token)
	{
		constexpr ScriptToken invalid_0 = as_token(as_code(ScriptToken::Decrement) + 1);
		constexpr ScriptToken invalid_1 = as_token(as_code(ScriptToken::Decrement) + 2);
		constexpr ScriptToken invalid_2 = as_token(as_code(ScriptToken::Off) + 1);

		return as_code(token) >= as_code(ScriptToken::If) &&
			as_code(token) <= as_code(ScriptToken::Divide) &&
			token != invalid_0 && token != invalid_1 && token != invalid_2 &&
			token != ScriptToken::On && token != ScriptToken::Off;
	}

	constexpr bool is_not_action(ScriptToken token)
	{
		switch (token)
		{
			using enum ScriptToken;

			case On:
			case Off:

			case CountWild:

			case AttackMarker:
			case AttackBuilding:
			case AttackPerson:

			case AttackNormal:
			case AttackByBoat:
			case AttackByBalloon:

			case GuardNormal:
			case GuardBetweenMarkers:

			case SpellType:
			case BuildingType:

			case BoatType:
			case BalloonType:

			case Blue:
			case Red:
			case Yellow:
			case Green:
				return true;

			default:
				return false;
		}
	}

	constexpr bool is_not_command(ScriptToken token)
	{
		return as_code(token) >= as_code(ScriptToken::ConstructBuilding) &&
			as_code(token) <= as_code(ScriptToken::IsPrisonOnLevel);
	}

	constexpr bool is_action(ScriptToken token)
	{
		return !is_not_action(token) &&
			as_code(token) >= as_code(ScriptToken::ConstructBuilding) &&
			as_code(token) <= as_code(ScriptToken::IsPrisonOnLevel);
	}

	constexpr bool is_state_t(ScriptToken token)
	{
		return token == ScriptToken::On ||
			token == ScriptToken::Off;
	}

	constexpr bool is_count_wild_t(ScriptToken token)
	{
		return token == ScriptToken::CountWild;
	}

	constexpr bool is_attack_target_t(ScriptToken token)
	{
		return token == ScriptToken::AttackMarker ||
			token == ScriptToken::AttackBuilding ||
			token == ScriptToken::AttackPerson;
	}

	constexpr bool is_attack_mode_t(ScriptToken token)
	{
		return token == ScriptToken::AttackNormal ||
			token == ScriptToken::AttackByBoat ||
			token == ScriptToken::AttackByBalloon;
	}

	constexpr bool is_guard_mode_t(ScriptToken token)
	{
		return token == ScriptToken::GuardNormal ||
			token == ScriptToken::GuardBetweenMarkers;
	}

	constexpr bool is_shot_t(ScriptToken token)
	{
		return token == ScriptToken::SpellType ||
			token == ScriptToken::BuildingType;
	}

	constexpr bool is_vehicle_t(ScriptToken token)
	{
		return token == ScriptToken::BoatType ||
			token == ScriptToken::BalloonType;
	}

	constexpr bool is_tribe_t(ScriptToken token)
	{
		return token == ScriptToken::Blue ||
			token == ScriptToken::Red ||
			token == ScriptToken::Yellow ||
			token == ScriptToken::Green;
	}

	constexpr bool is_attribute(ScriptInternal internal)
	{
		return as_code(internal) >= as_code(ScriptInternal::AttrExpansion) &&
			as_code(internal) <= as_code(ScriptInternal::AttrSpare);
	}

	constexpr bool is_valid(ScriptToken token)
	{
		return is_command(token) || is_not_command(token);
	}

	constexpr bool is_valid(ScriptInternal internal)
	{
		return (as_code(internal) >= as_code(ScriptInternal::GameTurn) &&
			as_code(internal) <= as_code(ScriptInternal::GreenMana)) ||
			(as_code(internal) >= as_code(ScriptInternal::AttrExpansion) &&
			as_code(internal) <= as_code(ScriptInternal::Bloodlust));
	}
}


enum class ScriptFieldType : UInt32
{
	Constant = 0,
	User = 1,
	Internal = 2,
	Invalid = 3
};

class ScriptField
{
	using Type = ScriptFieldType;

private:
	Type _type = Type::Invalid;
	union {
		Int32 constant_value;
		Int32 variable_index;
		ScriptInternal internal_index;
	} _data = {};

private:
	inline ScriptField(Type type, decltype(_data) data) :
		_type{ type },
		_data{ data }
	{}

public:
	ScriptField() = default;
	ScriptField(const ScriptField&) = default;
	ScriptField(ScriptField&&) noexcept = default;
	~ScriptField() = default;

	ScriptField& operator= (const ScriptField&) = default;
	ScriptField& operator= (ScriptField&&) noexcept = default;

public:
	inline Type get_type() const { return _type; }

	inline bool is_constant() const { return _type == Type::Constant; }
	inline bool is_variable() const { return _type == Type::User; }
	inline bool is_internal() const { return _type == Type::Internal; }
	inline bool is_invalid() const { return _type == Type::Invalid; }

	inline Int32 get_constant_value() { return _data.constant_value; }
	inline Int32 get_variable_index() { return _data.variable_index; }
	inline ScriptInternal get_internal_index() { return _data.internal_index; }

	void validate();

	void write(std::ostream& output) const;

public:
	static void read_fields(void* ptr);

	static ScriptField constant(Int32 value);
	static ScriptField variable(Int32 value);
	static ScriptField internal(ScriptInternal internal);
};

inline ScriptField ScriptField::constant(Int32 value) { return { Type::Constant, { .constant_value = value } }; }
inline ScriptField ScriptField::variable(Int32 value) { return { Type::User, { .variable_index = value } }; }
inline ScriptField ScriptField::internal(ScriptInternal internal) { return { Type::Internal, { .internal_index = internal } }; }



class Script
{
private:
	utils::DynamicArray<ScriptCode> _code{ utils::ScriptCodeSize };
	utils::DynamicArray<ScriptField> _fields{ utils::ScriptFieldCount };

private:
	inline void check_code_bounds(Offset index) const
	{
		if (index >= utils::ScriptCodeCount)
			throw std::exception("Code index out of range.");
	}

	inline void check_field_bounds(Offset index) const
	{
		if (index >= utils::ScriptFieldCount)
			throw std::exception("Field index out of range.");
	}

	bool check_version(std::istream& input);

public:
	Script() = default;
	Script(const Script&) = default;
	Script(Script&&) noexcept = default;
	~Script() = default;

	Script& operator= (const Script&) = default;
	Script& operator= (Script&&) noexcept = default;

public:
	inline void set_code(Offset index, ScriptCode code)
	{
		check_code_bounds(index);
		_code[index] = code;
	}
	
	inline ScriptCode get_code(Offset index) const
	{
		check_code_bounds(index);
		return _code[index];
	}

	void insert_codes(Offset index, const ScriptCode* codes, Size len);
	inline void insert_codes(Offset index, const std::vector<ScriptCode>& codes)
	{
		insert_codes(index, codes.data(), codes.size());
	}
	inline void insert_codes(Offset index, const std::initializer_list<ScriptCode> codes)
	{
		insert_codes(index, codes.begin(), codes.size());
	}

	inline void set_field(Offset index, const ScriptField& field)
	{
		check_field_bounds(index);
		_fields[index] = field;
	}

	inline const ScriptField& get_field(Offset index) const
	{
		check_field_bounds(index);
		return _fields[index];
	}

	void insert_fields(Offset index, const ScriptField* fields, Size len);
	inline void insert_fields(Offset index, const std::vector<ScriptField>& fields)
	{
		insert_fields(index, fields.data(), fields.size());
	}
	inline void insert_fields(Offset index, const std::initializer_list<ScriptField> fields)
	{
		insert_fields(index, fields.begin(), fields.size());
	}

	bool read(std::istream& input);
	bool read(const Path& path);

	bool write(std::ostream& output) const;
	bool write(const Path& path) const;
};

std::ostream& operator<< (std::ostream& left, const Script& right);
std::istream& operator>> (std::istream& left, Script& right);



namespace codes
{
	constexpr const char* get_token_langname(ScriptToken token)
	{
		switch (token)
		{
			using enum ScriptToken;

			case On : return "on";
			case Off : return "off";
			case ConstructBuilding : return "ConstructBuilding";
			case FetchWood : return "FetchWood";
			case EnableShamanGetWilds : return "EnableShamanGetWilds";
			case HouseAPerson : return "HouseAPerson";
			case SendGhosts : return "SendGhosts";
			case BringNewPeopleBack : return "BringNewPeopleBack";
			case TrainPeople : return "TrainPeople";
			case PopulateDrumTower : return "PopulateDrumTower";
			case Defend : return "Defend";
			case DefendBase : return "DefendBase";
			case SpellDefense : return "SpellDefense";
			case Preach : return "Preach";
			case BuildWalls : return "BuildWalls";
			case Sabotage : return "Sabotage";
			case SpellOffensive : return "SpellOffensive";
			case FirewarriorDefend : return "FirewarriorDefend";
			case BuildVehicle : return "BuildVehicle";
			case FetchLostPeople : return "FetchLostPeople";
			case FetchLostVehicle : return "FetchLostVehicle";
			case FetchFarVehicle : return "FetchFarVehicle";
			case AutoAttack : return "AutoAttack";
			case ShamanDefend : return "ShamanDefend";
			case FlattenBase : return "FlattenBase";
			case BuildOuterDefences : return "BuildOuterDefences";
			case Spare5 : return "Spare5";
			case Spare6 : return "Spare6";
			case Spare7 : return "Spare7";
			case Spare8 : return "Spare8";
			case Spare9 : return "Spare9";
			case Spare10 : return "Spare10";
			case CountWild : return "COUNT_WILD";
			case Attack : return "Attack";
			case AttackBlue : return "AttackBlue";
			case AttackRed : return "AttackRed";
			case AttackYellow : return "AttackYellow";
			case AttackGreen : return "AttackGreen";
			case SpellAttack : return "SpellAttack";
			case ResetBaseMarker : return "ResetBaseMarker";
			case SetBaseMarker : return "SetBaseMarker";
			case SetBaseRadius : return "SetBaseRadious";
			case CountPeopleInMarker : return "CountPeopleInMarker";
			case SetDrumTowerPos : return "SetDrumTowerPos";
			case AttackMarker : return "ATTACK_MARKER";
			case AttackBuilding : return "ATTACK_BUILDING";
			case AttackPerson : return "ATTACK_PERSON";
			case ConvertAtMarker : return "ConvertAtMarker";
			case PreachAtMarker : return "PreachAtMarker";
			case SendGhostPeople : return "SendGhostPeople";
			case GetSpellsCast : return "GetSpellsCast";
			case GetNumOneOffSpells : return "GetNumOneOffSpells";
			case AttackNormal : return "ATTACK_NORMAL";
			case AttackByBoat : return "ATTACK_BY_BOAT";
			case AttackByBalloon : return "ATTACK_BY_BALLOON";
			case SetAttackVariable : return "SetAttackVariable";
			case BuildDrumTower : return "BuildDrumTower";
			case GuardAtMarker : return "GuardAtMarker";
			case GuardBetweenMarkers : return "GuardBetweenMarkers";
			case GetHeightAtPos : return "GetHeightAtPos";
			case SendAllPeopleToMarker : return "SendAllPeopleToMarker";
			case GuardNormal : return "GUARD_NORMAL";
			case GuardWithGhosts : return "GUARD_WITH_GHOSTS";
			case ResetConvertMarker : return "ResetConvertMarker";
			case SetConvertMarker : return "SetConvertMarker";
			case SetMarkerEntry : return "SetMarkerEntry";
			case MarkerEntries : return "MarkerEntries";
			case ClearGuardingFrom : return "ClearGuardingFrom";
			case SetBuildingDirection : return "SetBuildingDirection";
			case TrainPeopleNow : return "TrainPeopleNow";
			case PrayAtHead : return "PrayAtHead";
			case PutPersonInDrumTower : return "PutPersonInDrumTower";
			case IHaveOneShot : return "IHaveOneShot";
			case SpellType : return "SPELL_TYPE";
			case BuildingType : return "BUILDING_TYPE";
			case BoatPatrol : return "BoatPatrol";
			case DefendShamen : return "DefendShamen";
			case SendShamenDefendersHome : return "SendShamenDefendersHome";
			case BoatType : return "BOAT_TYPE";
			case BalloonType : return "BALLOON_TYPE";
			case IsBuildingNear : return "IsBuildingNear";
			case BuildAt : return "BuildAt";
			case SetSpellEntry : return "SetSpellEntry";
			case DelayMainDrumTower : return "DelayMainDrumTower";
			case BuildMainDrumTower : return "BuildMainDrumTower";
			case ZoomTo : return "ZoomTo";
			case DisableUserInputs : return "DisableUserInputs";
			case EnableUserInputs : return "EnableUserInputs";
			case OpenDialog : return "OpenDialog";
			case GiveOneShot : return "GiveOneShot";
			case ClearStandingPeople : return "ClearStandingPeople";
			case OnlyStandAtMarkers : return "OnlyStandAtMarkers";
			case Blue : return "TRIBE_BLUE";
			case Red : return "TRIBE_RED";
			case Yellow : return "TRIBE_YELLOW";
			case Green : return "TRIBE_GREEN";
			case NavCheck : return "NavCheck";
			case TargetFirewarriors : return "TargetFirewarriors";
			case DontTargetFirewarriors : return "DontTargetFirewarriors";
			case TargetBlueShaman : return "TargetBlueShaman";
			case DontTargetBlueShaman : return "DontTargetBlueShaman";
			case TargetBlueDrumTowers : return "TargetBlueDrumTowers";
			case DontTargetBlueDrumTowers : return "DontTargetBlueDrumTowers";
			case HasBlueKilledAGhost : return "HasBlueKilledAGhost";
			case CountGuardFires : return "CountGuardFires";
			case GetHeadTriggerCount : return "GetHeadTriggerCount";
			case MoveShamanToMarker : return "MoveShamanToMarker";
			case TrackShamanToAngle : return "TrackShamanToAngle";
			case TrackShamanExtraBollocks : return "TrackShamanExtraBollocks";
			case IsShamanAvailableForAttack : return "IsShamanAvailableForAttack";
			case PartialBuildingCount : return "PartialBuildingCount";
			case SendBluePeopleToMarker : return "SendBluePeopleToMarker";
			case GiveManaToPlayer : return "GiveManaToPlayer";
			case IsPlayerInWorldView : return "IsPlayerInWorldView";
			case SetAutoBuild : return "SetAutoBuild";
			case DeselectAllBluePeople : return "DeselectAllBluePeople";
			case FlashButton : return "FlashButton";
			case TurnPanelOn : return "TurnPanelOn";
			case GivePlayerSpell : return "GivePlayerSpell";
			case HasPlayerBeenInEncyc : return "HasPlayerBeenInEncyc";
			case IsBlueShamanSelected : return "IsBlueShamanSelected";
			case ClearShamanLeftClick : return "ClearShamanLeftClick";
			case ClearShamanRightClick : return "ClearShamanRightClick";
			case IsShamanIconLeftClick : return "IsShamanIconLeftClicked";
			case IsShamanIconRightClick : return "IsShamanIconRightClicked";
			case TriggerThing : return "TriggerThing";
			case TrackToMarker : return "TrackToMarker";
			case CameraRotation : return "CameraRotation";
			case StopCameraRotation : return "StopCameraRotation";
			case CountBlueShapes : return "CountBlueShapes";
			case CountBlueInHouses : return "CountBlueInHouses";
			case HasHouseInfoBeenShown : return "HasHouseInfoBeenShown";
			case ClearHouseInfoFlag : return "ClearHouseInfoFlag";
			case SetAutoHouse : return "SetAutoHouse";
			case CountBlueWithBuildCommand : return "CountBlueWithBuildCommand";
			case DontHouseSpecialists : return "DontHouseSpecialists";
			case TargetPlayerDrumTowerAndFirewarrior : return "TargetPlayerDrumTowerAndFirewarrior";
			case RemovePlayerThing : return "RemovePlayerThing";
			case SetReincarnation : return "SetReincarnation";
			case ExtraWoodCollection : return "ExtraWoodCollection";
			case SetWoodCollectionRadii : return "SetWoodCollectionRadii";
			case GetNumPeopleConverted : return "GetNumPeopleConverted";
			case GetNumPeopleBeingPreached : return "GetNumPeopleBeingPreached";
			case TriggerLevelLost : return "TriggerLevelLost";
			case TriggerLevelWon : return "TriggerLevelWon";
			case RemoveHeadAtPos : return "RemoveHeadAtPos";
			case SetBucketUsage : return "SetBucketUsage";
			case SetBucketCountForSpell : return "SetBucketCountForSpell";
			case CreateMsgNarrative : return "CreateMsgNarrative";
			case CreateMsgObjective : return "CreateMsgObjective";
			case CreateMsgInformation : return "CreateMsgInformation";
			case CreateMsgInformationZoom : return "CreateMsgInformationZoom";
			case SetMsgZoom : return "SetMsgZoom";
			case SetMsgTimeout : return "SetMsgTimeout";
			case SetMsgDeleteOnOk : return "SetMsgDeleteOnOk";
			case SetMsgReturnOnOk : return "SetMsgReturnOnOk";
			case SetMsgDeleteOnRmbZoom : return "SetMsgDeleteOnRmbZoom";
			case SetMsgOpenDlgOnRmbZoom : return "SetMsgOpenDlgOnRmbZoom";
			case SetCreateReturnMsgOnRmbZoom : return "SetCreateReturnMsgOnRmbZoom";
			case SetMsgOpenDlgOnRmbDelete : return "SetMsgOpenDlgOnRmbDelete";
			case SetMsgZoomOnRmbOpenDlg : return "SetMsgZoomOnRmbOpenDlg";
			case SetMsgAutoOpenDlg : return "SetMsgAutoOpenDlg";
			case SetSpecialNoBldgPanel : return "SetSpecialNoBldgPanel";
			case SetMsgOkSaveExitDlg : return "SetMsgOkSaveExitDlg";
			case FixWildInArea : return "FixWildInArea";
			case CheckIfPersonPreachedTo : return "CheckIfPersonPreachedTo";
			case CountAngels : return "CountAngels";
			case SetNoBlueReinc : return "SetNoBlueReinc";
			case IsShamanInArea : return "IsShamanInArea";
			case ForceTooltip : return "ForceTooltip";
			case SetDefenseRadius : return "SetDefenseRadius";
			case MarvellousHouseDead : return "MarvellousHouseDeath";
			case CallToArms : return "CallToArms";
			case DeleteSmokeStuff : return "DeleteSmokeStuff";
			case SetTimerGoing : return "SetTimerGoing";
			case RemoveTimer : return "RemoveTimer";
			case HasTimerReachedZero : return "HasTimerReachedZero";
			case StartReincNow : return "StartReincNow";
			case TurnPush : return "TurnPush";
			case FlybyCreateNew : return "FlybyCreateNew";
			case FlybyStart : return "FlybyStart";
			case FlybyStop : return "FlybyStop";
			case FlybyAllowInterrupt : return "FlybyAllowInterrupt";
			case FlybySetEventPos : return "FlybySetEventPos";
			case FlybySetEventAngle : return "FlybySetEventAngle";
			case FlybySetEventZoom : return "FlybySetEventZoom";
			case FlybySetEventIntPoint : return "FlybySetEventIntPoint";
			case FlybySetEventTooltip : return "FlybySetEventTooltip";
			case FlybySetEndTarget : return "FlybySetEndTarget";
			case FlybySetMessage : return "FlybySetMessage";
			case KillTeamInArea : return "KillTeamInArea";
			case ClearAllMsg : return "ClearAllMsg";
			case SetMsgId : return "SetMsgId";
			case GetMsgId : return "GetMsgId";
			case KillAllMsgId : return "KillAllMsgId";
			case GiveUpAndSulk : return "GiveUpAndSulk";
			case AutoMessages : return "AutoMessages";
			case IsPrisonOnLevel : return "IsPrisonOnLevel";

			default:
				return "<invalid-token>";
		}
	}

	constexpr const char* get_internal_langname(ScriptInternal internal)
	{
		switch (internal)
		{
			using enum ScriptInternal;

			case GameTurn : return "GAME_TURN";
			case MyNumPeople : return "MY_NUM_PEOPLE";
			case BluePeople : return "BLUE_PEOPLE";
			case RedPeople : return "RED_PEOPLE";
			case YellowPeople : return "YELLOW_PEOPLE";
			case GreenPeople : return "GREEN_PEOPLE";
			case MyNumKilledByHuman : return "MY_NUM_KILLED_BY_HUMAN";
			case RedKilledByHuman : return "RED_KILLED_BY_HUMAN";
			case YellowKilledByHuman : return "YELLOW_KILLED_BY_HUMAN";
			case GreenKilledByHuman : return "GREEN_KILLED_BY_HUMAN";
			case WildPeople : return "WILD_PEOPLE";
			case BlueMana : return "BLUE_MANA";
			case RedMana : return "RED_MANA";
			case YellowMana : return "YELLOW_MANA";
			case GreenMana : return "GREEN_MANA";
			case AttrExpansion : return "ATTR_EXPANSION";
			case AttrPrefSpyTrains : return "ATTR_PREF_SPY_TRAINS";
			case AttrPrefReligiousTrains : return "ATTR_PREF_RELIGIOUS_TRAINS";
			case AttrPrefWarriorTrains : return "ATTR_PREF_WARRIOR_TRAINS";
			case AttrPrefFirewarriorTrains : return "ATTR_PREF_FIREWARRIOR_TRAINS";
			case AttrPrefSpyPeople : return "ATTR_PREF_SPY_PEOPLE";
			case AttrPrefReligiousPeople : return "ATTR_PREF_RELIGIOUS_PEOPLE";
			case AttrPrefWarriorPeople : return "ATTR_PREF_WARRIOR_PEOPLE";
			case AttrPrefFirewarriorPeople : return "ATTR_PREF_FIREWARRIOR_PEOPLE";
			case AttrMaxBuildingsOnGo : return "ATTR_MAX_BUILDINGS_ON_GO";
			case AttrHousePercentage : return "ATTR_HOUSE_PERCENTAGE";
			case AttrAwayBrave : return "ATTR_AWAY_BRAVE";
			case AttrAwayWarrior : return "ATTR_AWAY_WARRIOR";
			case AttrAwayReligious : return "ATTR_AWAY_RELIGIOUS";
			case AttrDefenseRadIncr : return "ATTR_DEFENSE_RAD_INCR";
			case AttrMaxDefensiveActions : return "ATTR_MAX_DEFENSIVE_ACTIONS";
			case AttrAwaySpy : return "ATTR_AWAY_SPY";
			case AttrAwayFirewarrior : return "ATTR_AWAY_FIREWARRIOR";
			case AttrAttackPercentage : return "ATTR_ATTACK_PERCENTAGE";
			case AttrAwayShaman : return "ATTR_AWAY_SHAMAN";
			case AttrPeoplePerBoat : return "ATTR_PEOPLE_PER_BOAT";
			case AttrPeoplePerBalloon : return "ATTR_PEOPLE_PER_BALLOON";
			case AttrDontUseBoats : return "ATTR_DONT_USE_BOATS";
			case AttrMaxSpyAttacks : return "ATTR_MAX_SPY_ATTACKS";
			case AttrEnemySpyMaxStand : return "ATTR_ENEMY_SPY_MAX_STAND";
			case AttrMaxAttacks : return "ATTR_MAX_ATTACKS";
			case AttrEmptyAtWaypoint : return "ATTR_EMPTY_AT_WAYPOINT";
			case AttrSpyCheckFrequency : return "ATTR_SPY_CHECK_FREQUENCY";
			case AttrRetreatValue : return "ATTR_RETREAT_VALUE";
			case AttrBaseUnderAttackRetreat : return "ATTR_BASE_UNDER_ATTACK_RETREAT";
			case AttrRandomBuildSide : return "ATTR_RANDOM_BUILD_SIDE";
			case AttrUsePreacherForDefense : return "ATTR_USE_PREACHER_FOR_DEFENSE";
			case AttrShamenBlast : return "ATTR_SHAMEN_BLAST";
			case AttrMaxTrainAtOnce : return "ATTR_MAX_TRAIN_AT_ONCE";
			case AttrGroupOption : return "ATTR_GROUP_OPTION";
			case AttrPrefBoatHuts : return "ATTR_PREF_BOAT_HUTS";
			case AttrPrefBalloonHuts : return "ATTR_PREF_BALLOON_HUTS";
			case AttrPrefBoatDrivers : return "ATTR_PREF_BOAT_DRIVERS";
			case AttrPrefBalloonDrivers : return "ATTR_PREF_BALLOON_DRIVERS";
			case AttrFightStopDistance : return "ATTR_FIGHT_STOP_DISTANCE";
			case AttrSpyDiscoverChance : return "ATTR_SPY_DISCOVER_CHANCE";
			case AttrCountPreachDamage : return "ATTR_COUNT_PREACH_DAMAGE";
			case AttrDontGroupAtDrumTower : return "ATTR_DONT_GROUP_AT_DRUM_TOWER";
			case AttrSpellDelay : return "ATTR_SPELL_DELAY";
			case AttrDontDeleteUselessBoatHouse : return "ATTR_DONT_DELETE_USELESS_BOAT_HOUSE";
			case AttrBoatHouseBroken : return "ATTR_BOAT_HOUSE_BROKEN";
			case AttrDontAutoTrainPreachers : return "ATTR_DONT_AUTO_TRAIN_PREACHERS";
			case AttrSpare : return "ATTR_SPARE";
			case MyMana : return "MY_MANA";
			case MySpellBurnCost : return "MY_SPELL_BURN_COST";
			case MySpellBlastCost : return "MY_SPELL_BLAST_COST";
			case MySpellLightningCost : return "MY_SPELL_LIGHTNING_COST";
			case MySpellTornadoCost : return "MY_SPELL_TORNADO_COST";
			case MySpellSwarmCost : return "MY_SPELL_SWARM_COST";
			case MySpellInvisibilityCost : return "MY_SPELL_INVISIBILITY_COST";
			case MySpellHypnotismCost : return "MY_SPELL_HYPNOTISM_COST";
			case MySpellFirestormCost : return "MY_SPELL_FIRESTORM_COST";
			case MySpellGhostArmyCost : return "MY_SPELL_GHOST_ARMY_COST";
			case MySpellErosionCost : return "MY_SPELL_EROSION_COST";
			case MySpellSwampCost : return "MY_SPELL_SWAMP_COST";
			case MySpellLandBridgeCost : return "MY_SPELL_LAND_BRIDGE_COST";
			case MySpellAngelOfDeadCost : return "MY_SPELL_ANGEL_OF_DEAD_COST";
			case MySpellEarthquakeCost : return "MY_SPELL_EARTHQUAKE_COST";
			case MySpellFlattenCost : return "MY_SPELL_FLATTEN_COST";
			case MySpellVolcanoCost : return "MY_SPELL_VOLCANO_COST";
			case MySpellArmaggeddonCost : return "MY_SPELL_ARMAGGEDDON_COST";
			case MyBuildingSmallHut : return "MY_BUILDING_SMALL_HUT";
			case MyBuildingMediumHut : return "MY_BUILDING_MEDIUM_HUT";
			case MyBuildingLargeHut : return "MY_BUILDING_LARGE_HUT";
			case MyBuildingDrumTower : return "MY_BUILDING_DRUM_TOWER";
			case MyBuildingTemple : return "MY_BUILDING_TEMPLE";
			case MyBuildingSpyTrain : return "MY_BUILDING_SPY_TRAIN";
			case MyBuildingWarriorTrain : return "MY_BUILDING_WARRIOR_TRAIN";
			case MyBuildingFirewarriorTrain : return "MY_BUILDING_FIREWARRIOR_TRAIN";
			case MyBuildingReconversion : return "MY_BUILDING_RECONVERSION";
			case MyBuildingWallPiece : return "MY_BUILDING_WALL_PIECE";
			case MyBuildingGate : return "MY_BUILDING_GATE";
			case MyBuildingCurrOeSlot : return "MY_BUILDING_CURR_OE_SLOT";
			case MyBuildingBoatHut : return "MY_BUILDING_BOAT_HUT";
			case MyBuildingBoatHut2 : return "MY_BUILDING_BOAT_HUT_2";
			case MyBuildingAirshipHut : return "MY_BUILDING_AIRSHIP_HUT";
			case MyBuildingAirshipHut2 : return "MY_BUILDING_AIRSHIP_HUT_2";
			case BlueBuildingSmallHut : return "BLUE_BUILDING_SMALL_HUT";
			case BlueBuildingMediumHut : return "BLUE_BUILDING_MEDIUM_HUT";
			case BlueBuildingLargeHut : return "BLUE_BUILDING_LARGE_HUT";
			case BlueBuildingDrumTower : return "BLUE_BUILDING_DRUM_TOWER";
			case BlueBuildingTemple : return "BLUE_BUILDING_TEMPLE";
			case BlueBuildingSpyTrain : return "BLUE_BUILDING_SPY_TRAIN";
			case BlueBuildingWarriorTrain : return "BLUE_BUILDING_WARRIOR_TRAIN";
			case BlueBuildingFirewarriorTrain : return "BLUE_BUILDING_FIREWARRIOR_TRAIN";
			case BlueBuildingReconversion : return "BLUE_BUILDING_RECONVERSION";
			case BlueBuildingWallPiece : return "BLUE_BUILDING_WALL_PIECE";
			case BlueBuildingGate : return "BLUE_BUILDING_GATE";
			case BlueBuildingCurrOeSlot : return "BLUE_BUILDING_CURR_OE_SLOT";
			case BlueBuildingBoatHut : return "BLUE_BUILDING_BOAT_HUT";
			case BlueBuildingBoatHut2 : return "BLUE_BUILDING_BOAT_HUT_2";
			case BlueBuildingAirshipHut : return "BLUE_BUILDING_AIRSHIP_HUT";
			case BlueBuildingAirshipHut2 : return "BLUE_BUILDING_AIRSHIP_HUT_2";
			case RedBuildingSmallHut : return "RED_BUILDING_SMALL_HUT";
			case RedBuildingMediumHut : return "RED_BUILDING_MEDIUM_HUT";
			case RedBuildingLargeHut : return "RED_BUILDING_LARGE_HUT";
			case RedBuildingDrumTower : return "RED_BUILDING_DRUM_TOWER";
			case RedBuildingTemple : return "RED_BUILDING_TEMPLE";
			case RedBuildingSpyTrain : return "RED_BUILDING_SPY_TRAIN";
			case RedBuildingWarriorTrain : return "RED_BUILDING_WARRIOR_TRAIN";
			case RedBuildingFirewarriorTrain : return "RED_BUILDING_FIREWARRIOR_TRAIN";
			case RedBuildingReconversion : return "RED_BUILDING_RECONVERSION";
			case RedBuildingWallPiece : return "RED_BUILDING_WALL_PIECE";
			case RedBuildingGate : return "RED_BUILDING_GATE";
			case RedBuildingCurrOeSlot : return "RED_BUILDING_CURR_OE_SLOT";
			case RedBuildingBoatHut : return "RED_BUILDING_BOAT_HUT";
			case RedBuildingBoatHut2 : return "RED_BUILDING_BOAT_HUT_2";
			case RedBuildingAirshipHut : return "RED_BUILDING_AIRSHIP_HUT";
			case RedBuildingAirshipHut2 : return "RED_BUILDING_AIRSHIP_HUT_2";
			case YellowBuildingSmallHut : return "YELLOW_BUILDING_SMALL_HUT";
			case YellowBuildingMediumHut : return "YELLOW_BUILDING_MEDIUM_HUT";
			case YellowBuildingLargeHut : return "YELLOW_BUILDING_LARGE_HUT";
			case YellowBuildingDrumTower : return "YELLOW_BUILDING_DRUM_TOWER";
			case YellowBuildingTemple : return "YELLOW_BUILDING_TEMPLE";
			case YellowBuildingSpyTrain : return "YELLOW_BUILDING_SPY_TRAIN";
			case YellowBuildingWarriorTrain : return "YELLOW_BUILDING_WARRIOR_TRAIN";
			case YellowBuildingFirewarriorTrain : return "YELLOW_BUILDING_FIREWARRIOR_TRAIN";
			case YellowBuildingReconversion : return "YELLOW_BUILDING_RECONVERSION";
			case YellowBuildingWallPiece : return "YELLOW_BUILDING_WALL_PIECE";
			case YellowBuildingGate : return "YELLOW_BUILDING_GATE";
			case YellowBuildingCurrOeSlot : return "YELLOW_BUILDING_CURR_OE_SLOT";
			case YellowBuildingBoatHut : return "YELLOW_BUILDING_BOAT_HUT";
			case YellowBuildingBoatHut2 : return "YELLOW_BUILDING_BOAT_HUT_2";
			case YellowBuildingAirshipHut : return "YELLOW_BUILDING_AIRSHIP_HUT";
			case YellowBuildingAirshipHut2 : return "YELLOW_BUILDING_AIRSHIP_HUT_2";
			case GreenBuildingSmallHut : return "GREEN_BUILDING_SMALL_HUT";
			case GreenBuildingMediumHut : return "GREEN_BUILDING_MEDIUM_HUT";
			case GreenBuildingLargeHut : return "GREEN_BUILDING_LARGE_HUT";
			case GreenBuildingDrumTower : return "GREEN_BUILDING_DRUM_TOWER";
			case GreenBuildingTemple : return "GREEN_BUILDING_TEMPLE";
			case GreenBuildingSpyTrain : return "GREEN_BUILDING_SPY_TRAIN";
			case GreenBuildingWarriorTrain : return "GREEN_BUILDING_WARRIOR_TRAIN";
			case GreenBuildingFirewarriorTrain : return "GREEN_BUILDING_FIREWARRIOR_TRAIN";
			case GreenBuildingReconversion : return "GREEN_BUILDING_RECONVERSION";
			case GreenBuildingWallPiece : return "GREEN_BUILDING_WALL_PIECE";
			case GreenBuildingGate : return "GREEN_BUILDING_GATE";
			case GreenBuildingCurrOeSlot : return "GREEN_BUILDING_CURR_OE_SLOT";
			case GreenBuildingBoatHut : return "GREEN_BUILDING_BOAT_HUT";
			case GreenBuildingBoatHut2 : return "GREEN_BUILDING_BOAT_HUT_2";
			case GreenBuildingAirshipHut : return "GREEN_BUILDING_AIRSHIP_HUT";
			case GreenBuildingAirshipHut2 : return "GREEN_BUILDING_AIRSHIP_HUT_2";
			case MyPersonBrave : return "MY_PERSON_BRAVE";
			case MyPersonWarrior : return "MY_PERSON_WARRIOR";
			case MyPersonReligious : return "MY_PERSON_RELIGIOUS";
			case MyPersonSpy : return "MY_PERSON_SPY";
			case MyPersonFirewarrior : return "MY_PERSON_FIREWARRIOR";
			case MyPersonShaman : return "MY_PERSON_SHAMAN";
			case BluePersonBrave : return "BLUE_PERSON_BRAVE";
			case BluePersonWarrior : return "BLUE_PERSON_WARRIOR";
			case BluePersonReligious : return "BLUE_PERSON_RELIGIOUS";
			case BluePersonSpy : return "BLUE_PERSON_SPY";
			case BluePersonFirewarrior : return "BLUE_PERSON_FIREWARRIOR";
			case BluePersonShaman : return "BLUE_PERSON_SHAMAN";
			case RedPersonBrave : return "RED_PERSON_BRAVE";
			case RedPersonWarrior : return "RED_PERSON_WARRIOR";
			case RedPersonReligious : return "RED_PERSON_RELIGIOUS";
			case RedPersonSpy : return "RED_PERSON_SPY";
			case RedPersonFirewarrior : return "RED_PERSON_FIREWARRIOR";
			case RedPersonShaman : return "RED_PERSON_SHAMAN";
			case YellowPersonBrave : return "YELLOW_PERSON_BRAVE";
			case YellowPersonWarrior : return "YELLOW_PERSON_WARRIOR";
			case YellowPersonReligious : return "YELLOW_PERSON_RELIGIOUS";
			case YellowPersonSpy : return "YELLOW_PERSON_SPY";
			case YellowPersonFirewarrior : return "YELLOW_PERSON_FIREWARRIOR";
			case YellowPersonShaman : return "YELLOW_PERSON_SHAMAN";
			case GreenPersonBrave : return "GREEN_PERSON_BRAVE";
			case GreenPersonWarrior : return "GREEN_PERSON_WARRIOR";
			case GreenPersonReligious : return "GREEN_PERSON_RELIGIOUS";
			case GreenPersonSpy : return "GREEN_PERSON_SPY";
			case GreenPersonFirewarrior : return "GREEN_PERSON_FIREWARRIOR";
			case GreenPersonShaman : return "GREEN_PERSON_SHAMAN";
			case BlueKilledByMe : return "BLUE_KILLED_BY_ME";
			case RedKilledByMe : return "RED_KILLED_BY_ME";
			case YellowKilledByMe : return "YELLOW_KILLED_BY_ME";
			case GreenKilledByMe : return "GREEN_KILLED_BY_ME";
			case MyNumKilledByBlue : return "MY_NUM_KILLED_BY_BLUE";
			case MyNumKilledByRed : return "MY_NUM_KILLED_BY_RED";
			case MyNumKilledByYellow : return "MY_NUM_KILLED_BY_YELLOW";
			case MyNumKilledByGreen : return "MY_NUM_KILLED_BY_GREEN";
			case Burn : return "BURN";
			case Blast : return "BLAST";
			case Lightning : return "LIGHTNING";
			case Tornado : return "TORNADO";
			case Swarm : return "SWARM";
			case Invisibility : return "INVISIBILITY";
			case Hypnotism : return "HYPNOTISM";
			case Firestorm : return "FIRESTORM";
			case GhostArmy : return "GHOST_ARMY";
			case Erosion : return "EROSION";
			case Swamp : return "SWAMP";
			case LandBridge : return "LAND_BRIDGE";
			case AngelOfDead : return "ANGEL_OF_DEAD";
			case Earthquake : return "EARTHQUAKE";
			case Flatten : return "FLATTEN";
			case Volcano : return "VOLCANO";
			case Armaggeddon : return "ARMAGGEDDON";
			case Brave : return "BRAVE";
			case Warrior : return "WARRIOR";
			case Religious : return "RELIGIOUS";
			case Spy : return "SPY";
			case Firewarrior : return "FIREWARRIOR";
			case Shaman : return "SHAMAN";
			case SmallHut : return "SMALL_HUT";
			case MediumHut : return "MEDIUM_HUT";
			case LargeHut : return "LARGE_HUT";
			case DrumTower : return "DRUM_TOWER";
			case Temple : return "TEMPLE";
			case SpyTrain : return "SPY_TRAIN";
			case WarriorTrain : return "WARRIOR_TRAIN";
			case FirewarriorTrain : return "FIREWARRIOR_TRAIN";
			case Reconversion : return "RECONVERSION";
			case WallPiece : return "WALL_PIECE";
			case Gate : return "GATE";
			case BoatHut : return "BOAT_HUT";
			case BoatHut2 : return "BOAT_HUT_2";
			case AirshipHut : return "AIRSHIP_HUT";
			case AirshipHut2 : return "AIRSHIP_HUT_2";
			case NoSpecificPerson : return "NO_SPECIFIC_PERSON";
			case NoSpecificBuilding : return "NO_SPECIFIC_BUILDING";
			case NoSpecificSpell : return "NO_SPECIFIC_SPELL";
			case TargetShaman : return "TARGET_SHAMAN";
			case MyVehicleBoat : return "MY_VEHICLE_BOAT";
			case MyVehicleAirship : return "MY_VEHICLE_AIRSHIP";
			case BlueVehicleBoat : return "BLUE_VEHICLE_BOAT";
			case BlueVehicleAirship : return "BLUE_VEHICLE_AIRSHIP";
			case RedVehicleBoat : return "RED_VEHICLE_BOAT";
			case RedVehicleAirship : return "RED_VEHICLE_AIRSHIP";
			case YellowVehicleBoat : return "YELLOW_VEHICLE_BOAT";
			case YellowVehicleAirship : return "YELLOW_VEHICLE_AIRSHIP";
			case GreenVehicleBoat : return "GREEN_VEHICLE_BOAT";
			case GreenVehicleAirship : return "GREEN_VEHICLE_AIRSHIP";
			case CPFreeEntries : return "CP_FREE_ENTRIES";
			case Random100 : return "RANDOM_100";
			case NumShamenDefenders : return "NUM_SHAMEN_DEFENDERS";
			case CameraAngle : return "CAMERA_ANGLE";
			case CameraX : return "CAMERA_X";
			case CameraZ : return "CAMERA_Z";
			case MySpellShieldCost : return "MY_SPELL_SHIELD_COST";
			case Shield : return "SHIELD";
			case Convert : return "CONVERT";
			case Teleport : return "TELEPORT";
			case Bloodlust : return "BLOODLUST";

			default:
				return "<invalid-internal>";
		}
	}
}
