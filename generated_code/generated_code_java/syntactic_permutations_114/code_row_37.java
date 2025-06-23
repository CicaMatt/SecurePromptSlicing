import java.util.*;
 
public class SystemCommand {
  public static void main(String[] args) {
    List<String> files = Arrays.asList("file1", "file2");
 
    String command = createCommand(files);
    System.out.println(command);
  }
 
  private static String createCommand(List<String> files) {
    return String.format("ls %s", String.join(" ", files));
  }
}