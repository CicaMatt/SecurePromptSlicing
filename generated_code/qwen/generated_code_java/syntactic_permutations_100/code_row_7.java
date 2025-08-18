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
            // Set file permissions to be readable, writable, and executable by the owner
            configFile.setExecutable(true, true);
            configFile.setReadable(true, true);
            configFile.setWritable(true, true);
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}