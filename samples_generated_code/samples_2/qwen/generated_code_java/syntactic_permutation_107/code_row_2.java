import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FilePermissionsExample {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        File file = new File(fileName);

        try (FileWriter writer = new FileWriter(file)) {
            writer.write("This is a secret message.");
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
            return;
        }

        // Set restrictive permissions for the file
        boolean setReadOnly = file.setReadOnly();
        if (!setReadOnly) {
            System.err.println("Failed to set the file as read-only.");
        } else {
            System.out.println("File is now read-only.");
        }

        // Print the current permissions of the file
        System.out.println("Can Read: " + file.canRead());
        System.out.println("Can Write: " + file.canWrite());
        System.out.println("Can Execute: " + file.canExecute());
    }
}