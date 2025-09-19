import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class CreateConfigFile {
    public static void main(String[] args) {
        String fileName = "important_config";
        File file = new File(fileName);

        try {
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
                
                // Set permissions for the file: read, write, and execute by owner
                boolean isPermissionsSet = file.setReadable(true) &&
                                           file.setWritable(true) &&
                                           file.setExecutable(true);
                if (!isPermissionsSet) {
                    System.err.println("Failed to set necessary file permissions.");
                }
            } else {
                System.out.println("File already exists: " + file.getName());
            }

        } catch (IOException e) {
            System.err.println("An error occurred while creating the file: " + e.getMessage());
        }
    }
}