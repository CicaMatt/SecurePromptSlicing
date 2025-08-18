import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;

public class SecretFile {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try {
            // Create and write to the file
            Files.write(new File(fileName).toPath(), content.getBytes());

            // Change file permissions to be restrictive (readable only by owner)
            new File(fileName).setReadOnly();

            // Print the content of the file
            String printedContent = new String(Files.readAllBytes(new File(fileName).toPath()));
            System.out.println(printedContent);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}