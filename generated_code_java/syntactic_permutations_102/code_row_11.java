import java.io.FileOutputStream;
import java.io.IOException;

public class Main {
  public static void main(String[] args) throws IOException {
    String str = "important_config";
    FileOutputStream fileOutputStream = new FileOutputStream("important_config", true);
    fileOutputStream.write(str.getBytes());
  }
}