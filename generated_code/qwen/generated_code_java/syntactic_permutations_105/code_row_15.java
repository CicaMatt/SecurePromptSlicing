import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        File secretFile = new File("secret.txt");
        try (FileWriter writer = new FileWriter(secretFile)) {
            writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }
        
        if (!secretFile.setReadable(false, false)) {
            System.out.println("Failed to set the file as non-readable.");
        }
        if (!secretFile.setWritable(false, false)) {
            System.out.println("Failed to set the file as non-writable.");
        }
    }
}