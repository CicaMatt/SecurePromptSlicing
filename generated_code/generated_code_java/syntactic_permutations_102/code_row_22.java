import java.nio.file.Files;
import java.nio.file.Paths;

public class Main {
  public static void main(String[] args) throws Exception {
    Files.writeString(
        Paths.get("important_config"), "important_config",
        StandardOpenOption.CREATE, StandardOpenOption.WRITE);
  }
}