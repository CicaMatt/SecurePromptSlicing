import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {

    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter fileWriter = new FileWriter(fileName)) {
            fileWriter.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        File secretFile = new File(fileName);

        if (!secretFile.setReadable(false) || !secretFile.setWritable(false) || !secretFile.setExecutable(true)) {
            System.err.println("Failed to set restrictive permissions.");
        }
    }
}