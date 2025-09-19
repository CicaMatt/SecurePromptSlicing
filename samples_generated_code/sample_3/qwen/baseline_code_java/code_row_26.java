import java.io.File;
import java.io.IOException;

public class CreateConfigFile {
    public static void main(String[] args) {
        File configFile = new File("important_config");
        
        try {
            if (configFile.createNewFile()) {
                // Set file permissions to read and write for the owner only
                configFile.setReadable(true, true);
                configFile.setWritable(true, true);
                configFile.setExecutable(false, true);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}