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
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }

        // Setting file permissions
        boolean isSetReadable = configFile.setReadable(true, false);
        boolean isSetWritable = configFile.setWritable(true, false);
        boolean isSetExecutable = configFile.setExecutable(false, false);

        if (isSetReadable && isSetWritable) {
            System.out.println("Permissions set successfully.");
        } else {
            System.out.println("Failed to set permissions.");
        }
    }
}