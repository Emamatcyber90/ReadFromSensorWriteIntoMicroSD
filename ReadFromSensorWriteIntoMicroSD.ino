/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

*/

#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("Initialization failed!");
    return;
  }
  Serial.println("Initialization done.");

  //creating file
  Serial.println("Enter file name without \".txt\".");
  String fileName = "";

  //  Serial.println(Serial.available());// 0
  //  Serial.println(Serial.read());//      -1
  while (1) {
    char myChar = Serial.read();
    if (myChar != -1 && myChar != '\n') {
      fileName += myChar;
    }
    if (myChar == '\n') {
      fileName += ".txt";
      //check if file exists
      if (SD.exists(fileName)) {
        Serial.println(fileName + " exists.");
        Serial.println("Content will be appended to file");
      } else {
        Serial.println(fileName + " does not exist.");
        Serial.println("Creating file \"" + fileName + "\"" );
      }
      break;
    }
  }



  //  /*
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  if (myFile) myFile.close(); //whatever file is open, close it.

  myFile = SD.open(fileName, FILE_WRITE);

  // if the file opened okay, write to it:
  if (!myFile) {
    // if the file didn't open, print an error:
    Serial.println("Error opening " + fileName);
  } else {

    Serial.println("File opened. Preparing to write to " + fileName + "...");
    Serial.println("Put in content string");
    myFile.println("1 2 3 4");
    Serial.println("1 2 3 4");
    int count = 0;

    while (2) {
      //      char contentChar  = Serial.read();       // get the character
      int contentInt  = Serial.read();       // get the ascii code
      //      while (contentInt != 255);//wait until a new cycle

      /*      if (contentInt == '\n') {
              count++;
              myFile.print("\n");
              Serial.print("    " );
              Serial.print( count );
              Serial.println( "th set of data");

            }
      */
//      int index = 0; //index in a set of data
//      if (index == 9) {
//        index = 0;
//        delay(10000);
//      }

      if (contentInt == 255) {
        count++;
        if (count != 1)myFile.print("\n");
        Serial.print("\n");
        Serial.print(count);
        Serial.print( "th set of data: ");
      }
      if ( contentInt  != -1) {
//        index++;
        myFile.print(contentInt);
        myFile.print(" ");
        Serial.print(contentInt);
        Serial.print(" ");
        //123}

        /*        if (contentInt == '%') {
                  Serial.println("\nContent added complete.");
                  break;
                }
        */

        if (count == 30) {
          Serial.println("\nContent added complete.");
          break;
        }
      }
    }

    // close the file:
    myFile.close();
    Serial.println("File closed.");
    Serial.println("checking in five seconds.");


    //wait 5 sec
    delay(5000);

    // re-open the file for reading:
    myFile = SD.open(fileName);
    if (!myFile) {
      // if the file didn't open, print an error:
      Serial.println("Error opening " + fileName);
    } else {
      Serial.println("content in " + fileName + ":");

      // read from the file until there's nothing else in it:
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      // close the file:
      myFile.close();
      Serial.println("\nFile closed. Mission accomplished.");
    }

    //  */

  }
}

void loop() {
  // nothing happens after setup
}


