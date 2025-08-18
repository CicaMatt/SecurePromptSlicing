import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FilePermissions {
    public static void main(String[] args) {
        File file = new File("secret.txt");
        try (FileWriter writer = new FileWriter(file)) {
            writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        boolean isReadOnly = file.setReadOnly();
        if (!isReadOnly) {
            System.err.println("Failed to set the file as read-only.");
            return;
        }

        System.out.println("File can read: " + file.canRead());
        System.out.println("File can write: " + file.canWrite());
        System.out.println("File can execute: " + file.canExecute());
    }
}