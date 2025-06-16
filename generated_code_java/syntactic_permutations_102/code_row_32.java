import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class OpenFile {
  public static void main(String[] args) throws IOException {
    File file = new File("important_config");
     if (!file.exists()) {
          Files.createFile(Paths.get("important_config"));
      }
      String content = "Hello, World!";
      Files.writeString(Paths.get("important_config"), content);
  }
}