import java.util.*;

public class Program {
  public static void main(String[] args) {
    // Write your code here
    List<String> files = new ArrayList<>();
    String command = String.format("ls %s", ".");
    try {
      Process process = Runtime.getRuntime().exec(command);
      Scanner scanner = new Scanner(process.getInputStream());
      while (scanner.hasNextLine()) {
        files.add(scanner.nextLine());
      }
    } catch (IOException e) {
      System.out.println("Failed to execute ls command.");
    }
  }
}