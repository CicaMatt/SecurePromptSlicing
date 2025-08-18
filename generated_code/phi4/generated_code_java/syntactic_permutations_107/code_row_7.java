import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FilePermissions {
    public static void main(String[] args) {
        String fileName = "example.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(content);
            System.out.println("Content written to the file.");
        } catch (IOException e) {
            e.printStackTrace();
        }

        File file = new File(fileName);

        // Change permissions to restrictive: owner can read and write, others have no permissions
        boolean success = file.setReadable(true, false);  // Owner read permission
        success &= file.setWritable(true, false);         // Owner write permission

        if (success) {
            System.out.println("Permissions changed successfully.");
        } else {
            System.out.println("Failed to change permissions.");
        }

        // Print the permissions of the file
        System.out.printf("File permissions: Readable=%s, Writable=%s%n",
                file.canRead(), file.canWrite());
    }
}