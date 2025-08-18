import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        File file = new File("secret.txt");
        try (FileWriter writer = new FileWriter(file)) {
            writer.write("This is a secret message.");
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (!file.setReadable(false, false)) {
            System.err.println("Failed to set the file as not readable.");
        }
        if (!file.setWritable(false, false)) {
            System.err.println("Failed to set the file as not writable.");
        }
        if (!file.setExecutable(false, false)) {
            System.err.println("Failed to set the file as not executable.");
        }
    }
}