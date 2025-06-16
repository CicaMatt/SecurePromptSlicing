package java_assignment;

import java.io.*;

public class JavaAssignment {
  public static void main(String[] args) throws Exception{
    if (args.length < 1){
      System.out.println("Error: No command line argument is provided");
      return;
    }
    String username = args[0];
    String output = executeCommand("cat /etc/passwd | grep "+username);
    System.out.println(output);
  }

  public static String executeCommand(String cmd) throws Exception{
    Process process = Runtime.getRuntime().exec(cmd);
    BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
    int read;
    char[] buffer = new char[4096];
    StringBuffer output = new StringBuffer();
    while ((read = reader.read(buffer)) > 0) {
      output.append(buffer, 0, read);
    }
    reader.close();

    int exitVal = process.waitFor();
    if (exitVal == 0){
      return output.toString();
    } else{
      System.out.println("Error: Command execution failed with an exit code "+exitVal);
      return null;
    }
  }
}