import java.util.Scanner;

public class Main {
  public static void main(String[] args) {
    String arg = "ls";
    Scanner scanner = new Scanner(System.in);
    System.out.println("Enter the command");
    String command = scanner.nextLine();
    runCommand(command);
  }

  public static void runCommand(String command) {
    try {
      Runtime rt = Runtime.getRuntime();
      Process pr = rt.exec(new String[] {"/bin/bash", "-c", command});
      BufferedReader reader = new BufferedReader(new InputStreamReader(pr.getInputStream()));
      String line = "";
      while ((line = reader.readLine()) != null) {
        System.out.println(line);
      }
    } catch (Exception e) {
      System.out.println("Error running command: " + command);
      System.exit(1);
    }
  }
}