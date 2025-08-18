import java.io.File;
import java.io.IOException;

public class CreateFileWithPermissions {

    public static void main(String[] args) {
        String filename = "example.txt";
        createFileWithPermissions(filename, 0644);
    }

    private static void createFileWithPermissions(String filename, int permissions) {
        File file = new File(filename);

        try {
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
            } else {
                System.out.println("File already exists.");
            }
            
            // Set the file permissions
            boolean success = file.setReadable(true, false);
            success &= file.setWritable(true, false);
            success &= file.setExecutable(false, false);

            if (success) {
                System.out.println("Permissions set successfully.");
            } else {
                System.out.println("Failed to set permissions.");
            }
        } catch (IOException e) {
            System.out.println("An error occurred: " + e.getMessage());
        }
    }
}