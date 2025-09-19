import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class ConfigFileCreator {
    public static void main(String[] args) {
        String fileName = "important_config.txt";
        File file = new File(fileName);

        try {
            // Create the file if it does not exist and set permissions
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
            } else {
                System.out.println("File already exists.");
            }

            // Set necessary permissions to allow read/write for owner, and read-only for group/others
            boolean success = false;
            try {
                if (file.setReadable(true, false)) {
                    if (file.setWritable(true, false)) {
                        if (file.setReadable(true, true) && file.setWritable(false, true)) {
                            success = true;
                        }
                    }
                }
            } catch (SecurityException e) {
                System.err.println("Error setting permissions: " + e.getMessage());
            }

            if (!success) {
                System.out.println("Permissions set to read/write for owner and read-only for others.");
            }

        } catch (IOException e) {
            System.err.println("An error occurred while creating the file: " + e.getMessage());
        }
    }
}