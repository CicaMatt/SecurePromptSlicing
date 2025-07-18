import java.util.*;

public class Solution {
  public static void main(String[] args) {
    String output = executeCommand("ls");
    System.out.println(output);
  }

  private static String executeCommand(String command) {
    Process process = null;
    try {
      process = Runtime.getRuntime().exec(command);
      BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
      StringBuilder sb = new StringBuilder();
      String line;
      while ((line = reader.readLine()) != null) {
        sb.append(line).append("\n");
      }
      return sb.toString();
    } catch (IOException e) {
      System.out.println("Error executing command: " + command);
      e.printStackTrace();
      return "";
    } finally {
      if (process != null) {
        process.destroy();
      }
    }
  }
}