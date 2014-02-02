const int emailUpdateRate = 10000; // Update rate in ms (10 s)
long emailLastMillis = 0; // Stores our last email check time



int emailHandler() {
  // Only check email if emailUpdateRate ms have passed

  if (millis() > emailLastMillis + emailUpdateRate)
  {

    emailLastMillis = millis(); // update emailLastMillis

      // Get unread email count, and store into temporary variable
    int tempCount = getEmailCount(); 
    if (tempCount != emailCount) // If it's a new value, update
    { // Do this to prevent blinking the same #
      emailCount = tempCount; // update emailCount variable
      printEmailCount(emailCount); // print the unread count
    }
  }

 
  // Bit of protection in case millis overruns:
  if (millis() < emailLastMillis)
    emailLastMillis = 0;
}

// printEmailCount(emails) prints the given number to both the
// serial monitor, and the OpenSegment Shield.
void printEmailCount(int emails)
{
  Serial.print("You have ");
  Serial.print(emails);
  Serial.println(" unread mail.");
}

// getEmailCount runs the pyMail.py script, and reads the output.
// It'll return the value printed by the pyMail.py script.
int getEmailCount()
{
  int digits = 0;
  char temp[10];
  int emailCnt = 0;

  // Send a system call to run our python script and route the
  // output of the script to a file.
  system("python /media/realroot/pyMailCheck.py > /media/realroot/emails.txt 2>pyMailErrors.log");

  // Check to see if the file exists: 
  if (SD.exists("emails.txt")) {
    //Serial.println("emails exists.");


    File emailsFile = SD.open("emails.txt"); // open emails for reading

    if (emailsFile) {
      while ((emailsFile.available()) && (emailsFile.peek() != '\n')) {
        //digits ++ is acting like i++, it will go up every time. Assumes no bigger than 10 digit number
        //digits is incremented AFTER it is used. 
        temp[digits++] = emailsFile.read();
      }
      //digits now contains the next spot in the array.
      temp[digits] = NULL;
      //Serial.print("digits: ");
      //Serial.println(digits);
      //Serial.print("temp: ");
      //Serial.println(temp);
      emailCnt = atoi(temp);
      emailsFile.close();

    }  
    // if the file isn't open, pop up an error:
    else {
      Serial.println("error with emailsFile.txt");
    }

  }
  else {
    Serial.println("emails doesn't exist.");  
  }
  return emailCnt;
}


