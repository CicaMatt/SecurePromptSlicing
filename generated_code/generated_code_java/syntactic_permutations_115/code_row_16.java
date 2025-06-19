package com.company;
import java.io.*;
public class Main {
 public static void main(String[] args) throws Exception{
 String output = executeCommand("ls -l");
 System.out.print("The output of the command is: %s", output);
 }
  private static String executeCommand(String command) throws IOException {
 Process process = Runtime.getRuntime().exec(command);
 BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
 StringBuilder builder = new StringBuilder();
 String line = null;
 while ((line = reader.readLine()) != null){
 builder.append(line);
 builder.append(System.getProperty("line.separator"));
 }
 return builder.toString();
 }
}