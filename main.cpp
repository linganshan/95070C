/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
 
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                   
// Pusher               digital_out   A              
// Expand               digital_out   B              
// Flywheel             motor_group   6, 8           
// Intake               motor_group   7, 11          
// DL                   motor_group   14, 16         
// DR                   motor_group   15, 17         
// Inertial             inertial      13             
// ---- END VEXCODE CONFIGURED DEVICES ----
 
#include "vex.h"
 
using namespace vex;
 
// A global instance of competition
competition Competition;
double x =1.5;
void TempCheck(){
 int drivetraintemp = (DR.temperature(percent)+DL.temperature(percent))/2;
 int flywheel = Flywheel.temperature(percent);
 int intake = Intake.temperature(percent);
 Controller1.Screen.setCursor(6, 1);
 Controller1.Screen.print(drivetraintemp);
 Controller1.Screen.setCursor(7, 1);
 Controller1.Screen.print(flywheel);
 Controller1.Screen.setCursor(7, 2);
 Controller1.Screen.print(intake);
}
double CircumWheel = M_PI*4;
double InchtoDegree(double Inch) {
return 360*Inch/CircumWheel;
};
/*void ForwardT(double Inch){
double Degrees = InchtoDegree(Inch);
//motor posibool takeIn=1;tion
DR.setPosition(0,degrees);
DL.setPosition(0,degrees);
//variable definition
double kp = 0.1;
//double ki = 0;
double kd = 0.1;
double currentDR = 0;
double currentDL = 0;
double LastErrorDR;
double LastErrorDL;
double PDR;
double PDL;
//double IDR;
//double IDL;
double DDR;
double DDL;
//P term
while(true){
double errorDR = Degrees - DR.position(degrees);
double errorDL = Degrees - DL.position(degrees);
if(errorDR == 0){
  DDR = 0;
}
if(errorDL == 0){
  DDL = 0;
}
double PDR = errorDR * kp;
double PDL = errorDL * kp;
double DDR = (errorDR-LastErrorDR) * kd;
double DDL = (errorDL-LastErrorDL) * kd;
LastErrorDR = errorDR;
LastErrorDL = errorDL;
currentDR = PDR + DDR;
currentDL = PDL + DDL;
Controller1.Screen.clearLine();
Controller1.Screen.print("Right: %d", currentDR);
Controller1.Screen.print("Left: %d", currentDL);
DR.spin(forward, currentDR, volt);
DL.spin(forward, currentDL, volt);
wait(0.5,seconds);
}
}*/
void Forward(double Inch){
double Degrees = InchtoDegree(Inch);
DR.spinFor(forward,Degrees,degrees,false);
DL.spinFor(forward,Degrees,degrees,true);
};
int we = 0;
void Flywheelstop(){
 we--;
 Flywheel.stop(coast);
}
 
void FlywheelPID(double Speed){
we ++;
double kpF = 0.1;
double kdF = 0.1;
double currentF=0;
double LastErrorF;
double PF;
double DF;
 while(we==1){
   double errorF = Speed - Flywheel.velocity(percent);
 
   double PF = errorF * kpF;
   double DF = (errorF-LastErrorF) * kdF;
  
   LastErrorF = errorF;
 
   currentF = PF + DF;
   Flywheel.spin(forward, currentF, volt);
   wait(20,msec);
 }
}
 
 
void TurnRight(int Spin){
DR.setVelocity(15,percent);
DL.setVelocity(15,percent);
DR.setStopping(hold);
DL.setStopping(hold);
Inertial.setRotation(0,degrees);
while(Inertial.rotation(degrees)<Spin){
DR.spin(reverse);
DL.spin(forward);
}
DR.stop();
DL.stop();
};
void TurnLeft(int Spin){
DR.setVelocity(15,percent);
DL.setVelocity(15,percent);
DR.setStopping(hold);
DL.setStopping(hold);
Inertial.setRotation(0,degrees);
while(360-Inertial.rotation(degrees)<Spin){
DL.spin(reverse);
DR.spin(forward);
}
DR.stop();
DL.stop();
};
/*void TurnRight(double degree){
FR.spinFor(reverse,degree,degrees,false);
BR.spinFor(reverse,degree,degrees,false);
FL.spinFor(forward,degree,degrees,false);
BL.spinFor(forward,degree,degrees,true);
};
void TurnLeft(double degree){
FR.spinFor(forward,degree,degrees,false);
BR.spinFor(forward,degree,degrees,false);
FL.spinFor(reverse,degree,degrees,false);
BL.spinFor(reverse,degree,degrees,true);
};*/
int auton = 1;
int noa = 8;
void autonselector() {
 if (auton>noa){
   auton=1;
 }
if (auton<1){
   auton=noa;
}
if(Controller1.Axis1.position(percent) > 5){
   auton++;
   wait(0.5,seconds);
}
if(Controller1.Axis1.position(percent) < -5){
   auton--;
   wait(0.5,seconds);
}
if(auton == 1){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("Sleep");
}
if(auton == 2){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("2");
}
if(auton == 3){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("R R1");
}
if(auton == 4){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("R R2");
}
if(auton == 5){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("R HG 6");
}
 if(auton == 6){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("L R1 HG 4");
 }
 if(auton == 7){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("R R1 LG2");
 }
 if(auton == 8){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("L R1 LG2");
 }
}
/*void auton8(){
 FR.setStopping(hold);
 FL.setStopping(hold);
 BR.setStopping(hold);
 BL.setStopping(hold);
 FR.setVelocity(15, percent);
 FL.setVelocity(15, percent);
 BR.setVelocity(15, percent);
 BL.setVelocity(15, percent);
 Flywheel.setVelocity(60,percent);
 Flywheel.setStopping(coast);
 Intake.setVelocity(80, percent);
 Intake.spin(reverse);
 Forward(1.25);
 Intake.stop();
 Forward(-3);
 TurnRight(140);
 Flywheel.spin(forward);
 wait(2, seconds);
 Pusher.set(true);
 wait(.1, seconds);
 Pusher.set(false);
 wait(500,msec);
 Pusher.set(true);
 wait(100,msec);
 Pusher.set(false);
 Flywheel.stop(coast);
}
void auton7(){
FR.setStopping(hold);
FL.setStopping(hold);
BR.setStopping(hold);
BL.setStopping(hold);
FR.setVelocity(15, percent);
FL.setVelocity(15, percent);
BR.setVelocity(15, percent);
BL.setVelocity(15, percent);
Forward(-1);
TurnLeft(130);
Forward(10);
TurnRight(132);
Intake.setVelocity(40, percent);
Intake.spin(reverse);
Forward(2.5);
Intake.stop();
Forward(-3);
TurnLeft(135);
Flywheel.setVelocity(65, percent);
Flywheel.spin(forward);
wait(2, seconds);
Pusher.set(true);
wait(.1, seconds);
Pusher.set(false);
wait(500,msec);
Pusher.set(true);
wait(100,msec);
Pusher.set(false);
wait(1, seconds);
Flywheel.stop(coast);
}
void auton6(){
 FR.setStopping(hold);
 FL.setStopping(hold);
 BR.setStopping(hold);
 BL.setStopping(hold);
 FR.setVelocity(15, percent);
 FL.setVelocity(15, percent);
 BR.setVelocity(15, percent);
 BL.setVelocity(15, percent);
 Flywheel.setVelocity(95,percent);
 Flywheel.setStopping(coast);
 Intake.setVelocity(80, percent);
 Intake.spin(reverse);
 Forward(1.25);
 Intake.stop();
 Forward(-1.5);
 wait(1, seconds);
 TurnLeft(18);
 Flywheel.spin(forward);
 wait(2,seconds);
 Pusher.set(true);
 wait(0.15, sec);
 Pusher.set(false);
 wait(.5,seconds);
 Flywheel.stop();
 Forward(-1);
 TurnLeft(162);
 Intake.spin(forward);
 FR.setVelocity(30, percent);
 FL.setVelocity(30, percent);
 BR.setVelocity(30, percent);
 BL.setVelocity(30, percent);
 Forward(22);
 wait(2.5, seconds);
 Intake.stop();
 TurnRight(140);
 Forward(-4);
 Flywheel.setVelocity(100, percent);
 Flywheel.spin(forward);
 wait(2, seconds);
 Pusher.set(true);
 wait(0.15, sec);
 Pusher.set(false);
 wait(.5, sec);
 Pusher.set(true);
 wait(0.15, sec);
 Pusher.set(false);
 wait(.3,seconds);
 Flywheel.stop();
 wait(3, sec);
 Intake.spin(forward);
 wait(1, seconds);
 Intake.stop();
 Flywheel.setVelocity(75, percent);
 Flywheel.spin(forward);
 wait(2, seconds);
 Pusher.set(true);
 wait(0.15, sec);
 Pusher.set(false);
 Flywheel.stop();
}
void auton5(){
 Forward(4);
 Intake.spin(forward);
 Forward(1);
 TurnRight(45);
 Flywheel.spin(forward);
 Intake.stop();
 wait(300, msec);
 Pusher.set(true);
 wait(100,msec);
 Pusher.set(false);
 wait(100, msec);
 Pusher.set(true);
 wait(100,msec);
 Pusher.set(false);
 wait(300,msec);
 Pusher.set(true);
 wait(100,msec);
 Pusher.set(false);
 TurnLeft(45);
 Intake.spin(forward);
 Forward(1);
 TurnRight(10);
 Forward(6);
 TurnRight(90);
 Forward(1);
 Intake.stop();
 Flywheel.spin(forward);
 Pusher.set(true);
 wait(100,msec);
 Pusher.set(false);
 wait(300,msec);
 Pusher.set(true);
 wait(100,msec);
 Pusher.set(false);
 Forward(-1);
 TurnLeft(90);
 Intake.spin(forward);
 Forward(1.5);
 TurnRight(135);
 Forward(1);
 Flywheel.spin(forward);
 Pusher.set(true);
 wait(100,msec);
 Pusher.set(false);
 
}
void auton4(){
 Forward(2);
 Intake.spinFor(reverse,150,degrees,true);
 Forward(-4);
 TurnLeft(190);
 Forward(14);
 TurnRight(120);
 Flywheel.spin(forward);
 Pusher.set(true);
 wait(0.15, sec);
 Pusher.set(false);
 wait(0.15, sec);
 Pusher.set(true);
 wait(0.15, sec);
 Pusher.set(false);
 wait(1,seconds);
 Flywheel.stop();
}
void auton3() {
 FR.setStopping(hold);
 FL.setStopping(hold);
 BR.setStopping(hold);
 BL.setStopping(hold);
 FR.setVelocity(15, percent);
 FL.setVelocity(15, percent);
 BR.setVelocity(15, percent);
 BL.setVelocity(15, percent);
 Forward(-2);
 TurnLeft(135);
 Forward(8);
 TurnRight(135);
 Intake.setVelocity(80, percent);
 Intake.spin(reverse);
 Forward(4);
 Intake.stop();
 Forward(-1);
}
void auton2() {
 FR.setStopping(hold);
 FL.setStopping(hold);
 BR.setStopping(hold);
 BL.setStopping(hold);
 FR.setVelocity(15, percent);
 FL.setVelocity(15, percent);
 BR.setVelocity(15, percent);
 BL.setVelocity(15, percent);
 Intake.setVelocity(80, percent);
 Intake.spin(reverse);
 Forward(1);
 Intake.stop();
 Forward(-2);
}*/
void auton2(){
Forward(10);
TurnRight(30);
Forward(-10);
FlywheelPID(900);
wait(4,seconds);
Flywheelstop();
}
void auton1() {
 wait(15,seconds);
}
 
// define your global instances of motors and other devices here
 
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
bool daviemonke;
bool katiemonkey;
bool vihaanisbest;
bool alangetbetter;
void pre_auton(void) {
 // Initializing Robot Configuration. DO NOT REMOVE!
 vexcodeInit();
 
 Intake.setVelocity(90,percent);
 daviemonke = 1;
katiemonkey = 1;
alangetbetter = 1;
vihaanisbest = 1;
 
 // All activities that occur before the competition starts
 // Example: learing encoders, setting servo positions, ...
}
 
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
 
void autonomous(void) {
if (auton == 1){
 auton1();
}
if (auton == 2){
 auton2();
}
/*
if (auton == 3) {
 auton3();
}
if (auton == 4) {
 auton4();
}
if (auton == 5) {
 auton5();
}
if (auton == 6) {
 auton6();
}
if (auton == 7){
 auton7();
}
if (auton == 8){
 auton8();
}*/
}
 
 
 // ..........................................................................
 
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
 
 
void usercontrol(void) {
 // User control code here, inside the loop
 while (1) {
    autonselector();
   TempCheck();
   // This is the main execution loop for the user control program.
   // Each time through the loop your program should update motor + servo
   // values based on feedback from the joysticks.
 
   // ........................................................................
 // ..........................................................................
 DL.setStopping(coast);
 DR.setStopping(coast);
 double right = (Controller1.Axis2.position() - (Controller1.Axis1.position()*0.65))/x;
 double left = (Controller1.Axis2.position() + (Controller1.Axis1.position()*0.65))/x;
 
 DL.spin(forward,left,percent);
 DR.spin(forward,right,percent);
 
if (Controller1.ButtonUp.pressing() && Controller1.ButtonLeft.pressing()){
 Expand.set(true);
}
 
if(alangetbetter) {
 if(Controller1.ButtonL1.pressing()){
   FlywheelPID(70);
   alangetbetter = false;
   wait(250,msec);
 }
}
 
else if(alangetbetter==0){
 if(Controller1.ButtonL1.pressing()){
   Flywheel.stop(coast);
   alangetbetter = true;
   wait(250, msec);
 }
}
 
if(katiemonkey) {
 if(Controller1.ButtonX.pressing()) {
   Intake.spin(reverse);
   katiemonkey = 0;
   wait(250,msec);
 }
}
if(katiemonkey== 0) {
 if(Controller1.ButtonX.pressing()) {
   Intake.stop();
   katiemonkey = 1;
   wait(250,msec);
 }
}
 
if(vihaanisbest) {
 if(Controller1.ButtonL2.pressing()){
   FlywheelPID(60);
   vihaanisbest = 0;
   wait(250,msec);
 }
}
 
else if(vihaanisbest==0) {
 if(Controller1.ButtonL2.pressing()) {
   Flywheelstop();
   vihaanisbest = 1;
   wait(250, msec);
 }
}
 
 
if(daviemonke) {
 if(Controller1.ButtonA.pressing()){
   Intake.spin(forward);
   daviemonke = false;
   wait(250,msec);
 }
 
}
 
else if(daviemonke==0) {
 if(Controller1.ButtonA.pressing()){
   Intake.stop();
   daviemonke = true;
   wait(250, msec);
 }
}
 
if (Controller1.ButtonR2.pressing()){
 Pusher.set(true);
 wait(.15, seconds);
 Pusher.set(false);
 wait(.5, seconds);
}
}
 
   // ........................................................................
 
   wait(20, msec); // Sleep the task for a short amount of time to
                   // prevent wasted resources.
 }
 
 
//
// Main will set up the competition functions and callbacks.
//
int main() {
 // Set up callbacks for autonomous and driver control periods.
 Competition.autonomous(autonomous);
 Competition.drivercontrol(usercontrol);
 
 // Run the pre-autonomous function.
 pre_auton();
 
 // Prevent main from exiting with an infinite loop.
 while (true) {
   wait(100, msec);
 }
}
 

