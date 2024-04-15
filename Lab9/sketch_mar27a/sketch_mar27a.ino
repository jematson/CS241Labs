void setup() {
 Serial.begin(57600);
 Serial.println("Demo ASCII comms!");
}




// Extract this numbered space-separated argument from the command
//   Example: num==1 and cmd=="rm /" => "rm"
//            num==2 and cmd=="rm /" => "/"
//            num==3 and cmd=="rm /" => ""
String extractArg(int num,String cmd)
{
 String arg="";
 int cur=1;
 bool justspaced=true;
 for (size_t i=0;i<cmd.length();i++)
 {
   char c = cmd[i];
   if (c==' ' || c=='\t') {
     if (justspaced) continue;
     if (cur==num) break; // done reading the arg they wanted
     arg="";
     cur++;
     justspaced=true;
   }
   else {
     arg += c;
     justspaced=false;
   }
 }
 if (cur==num) return arg;
 else return "";
}




// Execute one command
void runcmd(String cmdline)
{
 String cmd = extractArg(1,cmdline);
 Serial.print("running ");
 Serial.println(cmd);




 if (cmd=="") return; // empty command
 else if (cmd=="help") {
   Serial.println("PUT SOMETHING OTHER THAN FILLER HERE");
 }
 else if (cmd=="null") {
   int x = * (int *) NULL;
   Serial.println(x);
 }
 else if (cmd=="baud") {
   Serial.end();
   Serial.begin(19200);
   Serial.println("Are you reading this?");
 }
 else if (cmd=="new") {
   long* mem = malloc(512);
   Serial.println(*mem);
 }
 else if (cmd=="bounds") {
   int* arr = new int[3];
   Serial.println(arr[1000]);
 }
 else {
   Serial.print(cmd);
   Serial.println(" unrecognized");
 }
}




String cmdbuf;




void loop() {
 //Serial.write('a');
 while (Serial.available())
 {
   char c = Serial.read();
   if (c=='\n' || c=='\r') {  // some flavor of newline
     runcmd(cmdbuf); cmdbuf="";
   }
   else {
     cmdbuf+=c; // append char to command buffer
   }
 }
 delay(100);
}

