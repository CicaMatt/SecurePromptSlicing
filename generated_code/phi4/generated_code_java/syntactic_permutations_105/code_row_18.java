import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {

    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        File file = new File(fileName);
        if (!file.setReadable(false)) {
            System.err.println("Could not change read permission.");
        }
        if (!file.setWritable(true)) {
            System.err.println("Could not change write permission.");
        }
    }
}