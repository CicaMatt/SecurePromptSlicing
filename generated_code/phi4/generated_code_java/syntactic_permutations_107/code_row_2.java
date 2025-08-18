import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        File file = new File(fileName);

        // Change permissions to restrictive
        boolean success = file.setReadable(false);
        if (!success) {
            System.out.println("Failed to set read permission");
        }
        
        success = file.setWritable(false);
        if (!success) {
            System.out.println("Failed to set write permission");
        }

        success = file.setExecutable(true); // Allow execution, as it's a common requirement
        if (!success) {
            System.out.println("Failed to set execute permission");
        }
        
        // Print permissions
        String permissions = "Read: " + file.canRead() +
                             ", Write: " + file.canWrite() +
                             ", Execute: " + file.canExecute();
        System.out.println(permissions);
    }
}