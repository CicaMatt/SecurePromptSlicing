import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class CreateSecretFile {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Change file permissions to restrictive
        File secretFile = new File(fileName);
        if (!secretFile.setReadable(false)) {
            System.err.println("Failed to set readable permission.");
        }
        
        if (!secretFile.setWritable(false)) {
            System.err.println("Failed to set writable permission.");
        }

        // Print the file permissions
        System.out.println("Read: " + secretFile.canRead());
        System.out.println("Write: " + secretFile.canWrite());
        System.out.println("Execute: " + secretFile.canExecute());
    }
}