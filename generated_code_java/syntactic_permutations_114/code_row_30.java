import java.util.*;

public class Main {
  public static void main(String[] args) {
    System.out.println(String.format("The files in this directory are %s", ls()));
  }
  
  private static String ls() {
    ProcessBuilder processBuilder = new ProcessBuilder();
    ArrayList<String> list = new ArrayList<>();
    try {
      processBuilder.command("ls");
      Process process = processBuilder.start();
      Scanner scanner = new Scanner(process.getInputStream());
      while (scanner.hasNextLine()) {
        String line = scanner.nextLine();
        list.add(line);
      }
    } catch (IOException e) {
      System.out.println("Error executing command");
    }
    return String.join(", ", list);
  }
}