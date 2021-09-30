#pragma once

#include "common.h"

namespace utils
{
	constexpr int MaxCodes = 4095;
	constexpr int MaxFields = 512;
	constexpr int ScriptVersion = 12;
	constexpr int MaxVars = 64;

	constexpr int NoCommandModifier = 27;
	constexpr int TokenOffsetModifier = 1000;
	constexpr int InternalOffsetModifier = 1000;
}

typedef UInt16 ScriptCode;

#define token(_Code) (utils::TokenOffsetModifier + (_Code))
#define action(_Code) (token(_Code) + utils::NoCommandModifier)
#define internal(_Code) (utils::InternalOffsetModifier + (_Code))

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
	ShamanGetWild = action(3),
	HouseAPerson = action(4),
	SendGhosts = action(5),
	BeginNewPeopleBack = action(6),
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
	Spares5 = action(25),
	Spares6 = action(26),
	Spares7 = action(27),
	Spares8 = action(28),
	Spares9 = action(29),
	Spares10 = action(30),
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
	SendBluePeopleAtMarker = action(110),
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
	StopCameraRotationaction = action(127),
	CountBlueShapesaction = action(128),
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
	ExtraWoodCollectionRadii = action(139),
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
	SetMsgCreateReturnMsgOnRmbZoom = action(157),
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
	IsPrisionOnLevel = action(196)
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
	AttrMaxDefensiveAction = internal(15),
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
	MySpellHypnotistmCost = internal(55),
	MySpellFirestormCost = internal(56),
	MySpellGhostArmyCost = internal(57),
	MySpellErosionConst = internal(58),
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
	MyVehicleBalloon = internal(227),

	BlueVehicleBoat = internal(228),
	BlueVehicleBalloon = internal(229),

	RedVehicleBoat = internal(230),
	RedVehicleBalloon = internal(231),

	YellowVehicleBoat = internal(232),
	YellowVehicleBalloon = internal(233),

	GreenVehicleBoat = internal(234),
	GreenVehicleBalloon = internal(235),
	
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





namespace utils
{
	/*constexpr ScriptCommand as_command(ScriptCode code)
	{
		switch (static_cast<ScriptCommand>(code))
		{
			using enum ScriptCommand;

			case If:
			case Else:
			case Endif:
			case Begin:
			case End:
			case Every:
			case Do:
			case Set:
			case Increment:
			case Decrement:
			//case ExpStart:
			//case ExpEnd:
			case GreaterThan:
			case LessThan:
			case EqualTo:
			case NotEqualTo:
			case GreaterThanEqualTo:
			case LessThanEqualTo:
			case ScriptEnd:
			case And:
			case Or:
			//case On:
			//case Off:
			//case ComputerPlayer:
			case Multiply:
			case Divide:
				return static_cast<ScriptCommand>(code);

		default:
			return ScriptCommand::Invalid;
		}
	}
	constexpr bool is_invalid(ScriptCommand cmd) { return as_command(static_cast<ScriptCode>(cmd)) == ScriptCommand::Invalid; }
	constexpr bool is_command(ScriptCode code) { return as_command(code) != ScriptCommand::Invalid; }
	constexpr const char* get_command_name(ScriptCommand cmd)
	{
		switch (cmd)
		{
			using enum ScriptCommand;

			case If: return "if";
			case Else: return "else";
			case Endif: return "<endif-tag>";
			case Begin: return "<begin-tag>";
			case End: return "<end-tag>";
			case Every: return "every";
			case Do: return "<do-tag>";
			case Set: return "<set-tag>";
			case Increment: return "<increment-tag>";
			case Decrement: return "<decrement-tag>";
			//case ExpStart:
			//case ExpEnd:
			case GreaterThan: return "<greater-tag>";
			case LessThan: return "<less-tag>";
			case EqualTo: return "<equals-tag>";
			case NotEqualTo: return "<not-equals-tag>";
			case GreaterThanEqualTo: return "<greater-equals_tag>";
			case LessThanEqualTo: return "<less-equals-tag>";
			case ScriptEnd: return "<script-end-tag>";
			case And: return "<and-tag>";
			case Or: return "<or-tag>";
			//case On:
			//case Off:
			//case ComputerPlayer:
			case Multiply: return "<multiply-tag>";
			case Divide: return "<divide-tag>";

			default:
				return "<invalid>";
		}
	}*/
}
