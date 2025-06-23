import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileCreation {
  public static void main(String[] args) throws IOException{
      String important_config = "important_config";
      // Create an empty file if it doesn't exist
      Files.writeString(Paths.get(important_config), "", StandardOpenOption.CREATE);
      // Set read and write permissions for the owner and group, read-only for others
      File configFile = new File(important_config);
      boolean success = configFile.setReadable(true, true) && configFile.setWritable(true, true) && configFile.setExecutable(false, false) && configFile.setReadable(false, false);
  }
}