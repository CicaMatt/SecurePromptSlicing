import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FilePermissionExample {
    public static void main(String[] args) {
        String filePath = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter writer = new FileWriter(filePath)) {
            writer.write(content);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
            return;
        }

        File file = new File(filePath);

        // Set restrictive permissions
        boolean isReadOnlySet = file.setReadOnly();
        if (!isReadOnlySet) {
            System.err.println("Failed to set file as read-only.");
        }

        // Print current permissions
        String permissions = (file.canRead() ? "r" : "-") +
                            (file.canWrite() ? "w" : "-") +
                            (file.canExecute() ? "x" : "-");
        System.out.println("File permissions: " + permissions);
    }
}