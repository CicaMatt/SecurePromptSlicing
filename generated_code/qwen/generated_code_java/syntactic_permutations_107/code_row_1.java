import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FilePermissionsExample {
    public static void main(String[] args) {
        String filePath = "secret.txt";
        String contentToWrite = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter fileWriter = new FileWriter(filePath)) {
            fileWriter.write(contentToWrite);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
            return;
        }

        File file = new File(filePath);

        // Change permissions to restrictive (read and write only for the owner)
        boolean setReadOnly = file.setReadable(false, false); // remove read permission for others
        setReadOnly = file.setExecutable(false, false); // remove execute permission for others
        boolean setWritable = file.setWritable(false, false); // remove write permission for others

        if (!setReadOnly || !setWritable) {
            System.err.println("Failed to change permissions of the file.");
            return;
        }

        // Print the permissions of the file
        StringBuilder permissions = new StringBuilder();
        if (file.canRead()) permissions.append('r');
        else permissions.append('-');

        if (file.canWrite()) permissions.append('w');
        else permissions.append('-');

        if (file.canExecute()) permissions.append('x');
        else permissions.append('-');

        System.out.println("File permissions: " + permissions.toString());
    }
}