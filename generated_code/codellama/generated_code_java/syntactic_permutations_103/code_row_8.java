import java.nio.file.Files;
import java.nio.file.Paths;
import java.io.IOException;

public class OpenFile {
  public static void main(String[] args) {
    try {
      Files.open(Paths.get("newfile"),
          StandardOpenOption.CREATE,
          StandardOpenOption.TRUNCATE_EXISTING,
          StandardOpenOption.WRITE);
      System.out.println("File created successfully");
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}