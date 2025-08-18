import java.io.File;
import java.io.IOException;

public class ImportantConfigCreator {

    public static void main(String[] args) {
        String fileName = "important_config";
        
        try {
            // Create a new File object for the specified file.
            File file = new File(fileName);

            // Check if the file already exists
            if (!file.exists()) {
                boolean isCreated = file.createNewFile();
                
                if (isCreated) {
                    System.out.println("The file was created successfully.");
                    
                    // Set permissions: Read, Write and Execute for Owner, Group, and Others
                    boolean setPermissions = file.setReadable(true, false)
                                                && file.setWritable(true, false)
                                                && file.setExecutable(true, false);
                                                
                    if (setPermissions) {
                        System.out.println("The necessary permissions have been set.");
                    } else {
                        System.err.println("Failed to set the necessary permissions.");
                    }
                } else {
                    System.err.println("Failed to create the new file.");
                }
            } else {
                System.out.println("The file already exists.");
            }

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}