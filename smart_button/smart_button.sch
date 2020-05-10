EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:WeMos_D1_mini U1
U 1 1 5EB89AAA
P 2100 2000
F 0 "U1" H 2100 1111 50  0000 C CNN
F 1 "WeMos_D1_mini" H 2100 1020 50  0000 C CNN
F 2 "Module:WEMOS_D1_mini_light" H 2100 850 50  0001 C CNN
F 3 "https://wiki.wemos.cc/products:d1:d1_mini#documentation" H 250 850 50  0001 C CNN
	1    2100 2000
	1    0    0    -1  
$EndComp
$Comp
L pspice:CAP C1
U 1 1 5EB8B577
P 1150 1950
F 0 "C1" H 972 1904 50  0000 R CNN
F 1 "0.1uF" H 972 1995 50  0000 R CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P2.00mm" H 1150 1950 50  0001 C CNN
F 3 "~" H 1150 1950 50  0001 C CNN
	1    1150 1950
	-1   0    0    1   
$EndComp
Text GLabel 2000 1000 1    50   Input ~ 0
Vin
Wire Wire Line
	2000 1000 2000 1150
Wire Wire Line
	2100 2950 2100 2850
Text GLabel 2100 2950 3    50   Input ~ 0
GND
Wire Wire Line
	1150 1700 1150 1150
Wire Wire Line
	1150 1150 2000 1150
Connection ~ 2000 1150
Wire Wire Line
	2000 1150 2000 1200
Wire Wire Line
	1150 2200 1150 2850
Wire Wire Line
	1150 2850 2100 2850
Connection ~ 2100 2850
Wire Wire Line
	2100 2850 2100 2800
$Comp
L DFplayer_mini:TTP223_TOUCH1 U2
U 1 1 5EB8F673
P 3900 1350
F 0 "U2" H 4103 1345 60  0000 L CNN
F 1 "TTP223_TOUCH1" H 4103 1239 60  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 3900 1350 60  0001 C CNN
F 3 "" H 3900 1350 60  0000 C CNN
	1    3900 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 1200 2200 1150
Wire Wire Line
	2200 1150 3500 1150
Wire Wire Line
	3500 1150 3500 1800
Wire Wire Line
	3500 1800 3800 1800
Wire Wire Line
	3800 1800 3800 1750
Wire Wire Line
	4000 1750 4000 2200
Wire Wire Line
	4000 2850 2100 2850
Wire Wire Line
	3900 1750 3900 2000
Wire Wire Line
	3900 2000 3500 2000
$Comp
L pspice:CAP C2
U 1 1 5EB91E07
P 3750 2200
F 0 "C2" V 4065 2200 50  0000 C CNN
F 1 "0.1uF" V 3974 2200 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P2.00mm" H 3750 2200 50  0001 C CNN
F 3 "~" H 3750 2200 50  0001 C CNN
	1    3750 2200
	0    -1   -1   0   
$EndComp
Connection ~ 4000 2200
Wire Wire Line
	4000 2200 4000 2850
Wire Wire Line
	3500 2200 3500 2000
Connection ~ 3500 2000
Wire Wire Line
	3500 2000 2500 2000
$EndSCHEMATC
