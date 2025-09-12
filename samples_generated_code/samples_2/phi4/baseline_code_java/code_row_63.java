import java.io.File;
import java.io.IOException;

public class CreateConfigFile {
    public static void main(String[] args) {
        File configFile = new File("important_config.txt");

        try {
            if (configFile.createNewFile()) {
                System.out.println("The file was successfully created.");
                
                // Setting permissions on Unix/Linux systems
                boolean isUnix = !System.getProperty("os.name").toLowerCase().contains("windows");
                if (isUnix) {
                    configFile.setReadable(true);
                    configFile.setWritable(true);
                    configFile.setExecutable(true);
                }
            } else {
                System.out.println("The file already exists.");
            }
        } catch (IOException e) {
            System.err.println("An error occurred while creating the file: " + e.getMessage());
        }
    }
}