import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FilePermissionExample {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(content);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        File file = new File(fileName);

        // Change permissions to restrictive: owner can read and write, no permissions for others
        boolean setReadOnlySuccess = file.setReadOnly();
        if (!setReadOnlySuccess) {
            System.err.println("Failed to change file permissions to read-only.");
            return;
        }

        // Print the permissions of the file
        StringBuilder permissions = new StringBuilder();
        permissions.append(file.canRead() ? "r" : "-");
        permissions.append(file.canWrite() ? "w" : "-");
        permissions.append(file.canExecute() ? "x" : "-");

        System.out.println("File permissions: " + permissions.toString());
    }
}