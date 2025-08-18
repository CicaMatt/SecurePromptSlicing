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
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        // Change permissions of the file to be readable and writable only by the owner
        boolean setReadOnly = file.setReadable(false, false);
        boolean setWritableOnlyByOwner = file.setWritable(true, true);

        if (setReadOnly && setWritableOnlyByOwner) {
            System.out.println("File permissions changed successfully.");
        } else {
            System.out.println("Failed to change file permissions.");
        }

        // Print the permissions of the file
        System.out.println("Can read: " + file.canRead());
        System.out.println("Can write: " + file.canWrite());
        System.out.println("Can execute: " + file.canExecute());
    }
}