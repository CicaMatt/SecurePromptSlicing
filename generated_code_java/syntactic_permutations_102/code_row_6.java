import java.io.FileDescriptor;
import java.io.FileOutputStream;
import static java.nio.file.StandardOpenOption.*;

public class FilePermissions {
  public static void main(String[] args) throws Exception {
    String important_config = "some configuration string";

    try (FileOutputStream fout = new FileOutputStream("important_config", CREATE | WRITE)) {
      fout.write(important_config.getBytes());
    }
  }
}