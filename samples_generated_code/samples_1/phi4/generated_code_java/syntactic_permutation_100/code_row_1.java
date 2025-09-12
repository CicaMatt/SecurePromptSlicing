import java.io.File;
import java.io.IOException;

public class CreateConfigFile {

    public static void main(String[] args) {
        try {
            File configFile = new File("important_config");
            boolean fileCreated = configFile.createNewFile();

            if (fileCreated || configFile.exists()) {
                // Set the necessary permissions: Read, Write for owner; Read for group and others
                int perms = (configFile.getOwnerPermission() & 0666) | 
                            (configFile.getGroupPermission() & 0066) | 
                            (configFile.getOthersPermission() & 0006);
                
                configFile.setPermissions(perms);

                System.out.println("File created with necessary permissions.");
            } else {
                System.err.println("Failed to create the file.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}