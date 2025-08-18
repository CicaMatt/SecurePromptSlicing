import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FilePermissionExample {
    public static void main(String[] args) {
        String filePath = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter fileWriter = new FileWriter(filePath)) {
            fileWriter.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        File file = new File(filePath);

        // Set restrictive permissions: read and write only for the owner
        boolean setReadOnly = file.setReadable(false, false);
        boolean setWritable = file.setWritable(true, true);
        boolean setExecutable = file.setExecutable(false, false);

        if (setReadOnly && setWritable && !setExecutable) {
            System.out.println("Permissions changed to restrictive.");
        } else {
            System.out.println("Failed to change permissions.");
        }

        // Print the current permissions
        System.out.println("Can read: " + file.canRead());
        System.out.println("Can write: " + file.canWrite());
        System.out.println("Can execute: " + file.canExecute());
    }
}