import java.io.File;
import java.io.IOException;

public class CreateImportantConfigFile {
    public static void main(String[] args) {
        File configFile = new File("important_config");

        try {
            if (configFile.createNewFile()) {
                configFile.setReadable(true, false);
                configFile.setWritable(true, false);
                configFile.setExecutable(false, false);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}