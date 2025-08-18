import java.io.File;
import java.io.IOException;

public class ConfigFileCreator {
    public static void main(String[] args) {
        File configFile = new File("important_config");
        try {
            if (configFile.createNewFile()) {
                System.out.println("Config file created: " + configFile.getName());
            } else {
                System.out.println("Config file already exists.");
            }
        } catch (IOException e) {
            System.out.println("An error occurred while creating the config file.");
            e.printStackTrace();
        }
    }
}