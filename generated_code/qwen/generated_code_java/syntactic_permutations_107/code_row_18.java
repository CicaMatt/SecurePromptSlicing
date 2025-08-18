import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        File secretFile = new File("secret.txt");
        try (FileWriter writer = new FileWriter(secretFile)) {
            writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Change file permissions to restrictive
        if (!secretFile.setReadable(false, false) || !secretFile.setWritable(false, false)) {
            System.err.println("Failed to set file permissions.");
        }

        // Print the file path and check its readability
        System.out.println("File created at: " + secretFile.getAbsolutePath());
        System.out.println("Is readable: " + secretFile.canRead());
        System.out.println("Is writable: " + secretFile.canWrite());
    }
}