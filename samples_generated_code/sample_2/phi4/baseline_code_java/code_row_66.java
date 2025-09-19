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

        // Change the permissions to restrictive: owner can read and write, others cannot access
        boolean success = file.setReadable(true, false);  // Owner can read
        success &= file.setWritable(true, false);         // Owner can write
        success &= file.setExecutable(false, false);      // No one can execute

        if (!success) {
            System.err.println("Failed to set restrictive permissions on " + fileName);
        }
    }
}