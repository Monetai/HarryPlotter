
boolean WaitForNextCommand(char *commandBuffer)
{
    long currentTime = millis();
    int bufferPos = 0;
    //reset buffer
    ClearBuffer(commandBuffer, &bufferPos);

    boolean terminated = false;
    long lastExecutionTime = 0L;
    
    while (!terminated)
    { 
      long timeSince = millis() - lastExecutionTime;
      
      // If the buffer is being filled, but hasn't received a new char in less than 100ms,
      // just cancel it. It's probably just junk.
      if (bufferPos != 0 && timeSince > 100)
      {
    #ifdef DEBUG_COMMS
        Serial.print(F("Timed out:"));
        Serial.println(timeSince);
    #endif
        ClearBuffer(commandBuffer, &bufferPos);
      }
      
      timeSince = millis() - currentTime;
      if (timeSince > REBROADCAST_READY_INTERVAL)
      {
        // Send a READY every 5000ms of idling
    #ifdef DEBUG_COMMS      
        Serial.println("");
    #endif
        SendCommandReady();
        currentTime = millis();
      }
      
      // And now read the command if one exists.
      if (Serial.available() > 0)
      {
        // Get the char
        char ch = Serial.read();
    #ifdef DEBUG_COMMS
        Serial.print(F("received char: "));
        Serial.println(ch);
    #endif
        
        // look at it, if it's a terminator, then lets terminate the string
        if ( ch == COMMAND_SEMICOLON) {
          
          commandBuffer[bufferPos] = 0; // null terminate the string
          terminated = true;
          
    #ifdef DEBUG_COMMS
          Serial.println(F("Received command terminated!"));
    #endif
    
          //clear remaining character
          for (int i = bufferPos; i < COMMAND_BUFFER_LENGHT-1; i++) {
            commandBuffer[i] = 0;
          }
          
        } else {
          // otherwise, just add it into the buffer
          commandBuffer[bufferPos] = ch;
          bufferPos++;
        }
        
    #ifdef DEBUG_COMMS
        Serial.print(F("commandBuffer: "));
        Serial.println(commandBuffer);
        Serial.print(F("Buffer Pos: "));
        Serial.println(bufferPos);
    #endif
        lastExecutionTime = millis();
      }
    }
    return true;
}

void ClearBuffer(char *commandBuffer, int *bufferPos)
{
    for (int i = 0; i < COMMAND_BUFFER_LENGHT; i++) {
      commandBuffer[i] = 0;
    }  
    bufferPos = 0;
}

void ParseAndExecuteCommand(char *commandBuffer)
{
  boolean commandParsed = ParseCommand(commandBuffer);
  if (commandParsed)
  {
    //impl_processCommand(lastCommand);
    commandConfirmed = false;
    SendCommandReady();
  }
  numberOfCommandParams = 0;
}

boolean ParseCommand(char *commandBuffer)
{
  return true;
}

void ExtractCommandParams(char *commandBuffer)
{
  
}

void SendCommandReady()
{
  Serial.println(F(READY_CMD));
}

void SendCommandDrawing()
{
  Serial.println(F(DRAWING_CMD));
}

void SendRequestResend()
{
  Serial.println(F(RESEND_CMD));
}

void SendUnrecognisedCommand(String &com)
{
  Serial.print(UNRECOGNISED_E_MSG);
  Serial.print(com);
  Serial.println(F(" not recognised."));
}
