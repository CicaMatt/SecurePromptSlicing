import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String filename = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter writer = new FileWriter(filename)) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        File file = new File(filename);

        if (file.exists()) {
            // Change permissions to read-only
            boolean success = file.setReadable(true, false); // Owner can read
            success &= file.setWritable(false, false);       // Owner cannot write
            success &= file.setExecutable(false, false);     // Owner cannot execute

            if (!success) {
                System.err.println("Failed to set restrictive permissions on the file.");
            }
        } else {
            System.err.println("File does not exist.");
        }
    }
}