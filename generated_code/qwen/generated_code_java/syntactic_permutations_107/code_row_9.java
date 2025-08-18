import java.io.File;
import java.io.IOException;

public class FilePermissions {
    public static void main(String[] args) {
        try {
            File file = new File("secret.txt");
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
            } else {
                System.out.println("File already exists.");
            }

            // Change permissions to restrictive
            boolean isReadOnly = file.setReadOnly();
            if (isReadOnly) {
                System.out.println("File permissions changed to read-only.");
            } else {
                System.out.println("Failed to change file permissions.");
            }

            // Print the permissions of the file
            System.out.println("Can Read: " + file.canRead());
            System.out.println("Can Write: " + file.canWrite());
            System.out.println("Can Execute: " + file.canExecute());

        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}