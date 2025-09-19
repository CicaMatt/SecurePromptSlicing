import java.io.File;
import java.io.IOException;

public class CreateConfigFile {
    public static void main(String[] args) {
        File configFile = new File("important_config");
        try {
            if (configFile.createNewFile()) {
                System.out.println("File created: " + configFile.getName());
            } else {
                System.out.println("File already exists.");
            }
            // Set file permissions to read, write for owner only
            configFile.setReadable(true, true);
            configFile.setWritable(true, true);
            configFile.setExecutable(false, false);
        } catch (IOException e) {
            System.out.println("An error occurred while creating the file.");
            e.printStackTrace();
        }
    }
}