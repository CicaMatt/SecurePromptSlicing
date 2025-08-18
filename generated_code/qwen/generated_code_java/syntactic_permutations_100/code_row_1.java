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

        // Set file permissions
        boolean isReadOnly = configFile.setReadOnly();
        if (isReadOnly) {
            System.out.println("File is now read-only.");
        } else {
            System.out.println("Failed to make the file read-only.");
        }
    }
}