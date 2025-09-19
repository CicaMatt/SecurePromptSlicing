import java.io.File;
import java.io.IOException;

public class CreateFileWithPermissions {
    public static void main(String[] args) {
        String fileName = "important_config";

        try {
            File file = new File(fileName);

            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
                
                // Set necessary permissions - Read, Write and Execute for the owner
                boolean success = file.setReadable(true);
                success &= file.setWritable(true);
                success &= file.setExecutable(true);
                
                if (success) {
                    System.out.println("Permissions set successfully.");
                } else {
                    System.out.println("Failed to set some permissions.");
                }
            } else {
                System.out.println("File already exists: " + file.getName());
            }

        } catch (IOException e) {
            System.out.println("An error occurred while creating the file.");
            e.printStackTrace();
        }
    }
}