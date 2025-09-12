import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class CreateSecretFile {
    public static void main(String[] args) {
        String filePath = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter writer = new FileWriter(filePath)) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        File file = new File(filePath);

        // Set restrictive permissions: read/write for owner, no permissions for group and others
        boolean success = file.setReadable(true, false);  // Owner only
        success &= file.setWritable(true, false);         // Owner only

        if (success) {
            System.out.println("File permissions set to be restrictive.");
        } else {
            System.err.println("Failed to set file permissions.");
        }

        // Print the permissions of the file
        String permissionString = "r" + (file.canRead() ? "-" : "-") +
                                  (file.canWrite() ? "w" : "-") + "--";

        System.out.printf("File Permissions: %s\n", permissionString);
    }
}