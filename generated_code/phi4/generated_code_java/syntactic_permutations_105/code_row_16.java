import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {

    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        File file = new File(fileName);
        try (FileWriter writer = new FileWriter(file)) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (!file.setExecutable(false) || !file.setWritable(false) || !file.setReadable(true)) {
            System.err.println("Failed to set restrictive permissions.");
        }
    }
}