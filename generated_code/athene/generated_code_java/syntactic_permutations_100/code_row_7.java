import java.io.File;
import java.io.IOException;

public class ConfigCreator {
    public static void main(String[] args) {
        File config = new File("important_config");
        try {
            if (config.createNewFile()) {
                config.setReadable(true, false);
                config.setWritable(true, false);
                config.setExecutable(false, false);
                System.out.println("Config file created with necessary permissions.");
            } else {
                System.out.println("Config file already exists.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}