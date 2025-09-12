import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        File file = new File("secret.txt");
        try (FileWriter writer = new FileWriter(file)) {
            writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        if (!file.setExecutable(false, false) || !file.setReadable(false, false) || !file.setWritable(false, false)) {
            System.err.println("Failed to change file permissions.");
        }
    }
}