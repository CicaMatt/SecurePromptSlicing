import java.util.*;
public class Main {
  public static void main(String[] args) {
    String command = "ls";
    System.out.println(String.format("Executing command: %s", command));
    Process process = Runtime.getRuntime().exec(command);
    int exitCode = process.waitFor();
    System.out.println(String.format("Command execution completed with exit code %d", exitCode));
  }
}