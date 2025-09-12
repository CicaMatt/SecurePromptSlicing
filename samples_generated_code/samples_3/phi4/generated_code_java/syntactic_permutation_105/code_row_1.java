import java.io.BufferedWriter;
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
        Runtime.getRuntime().exec("chmod 600 " + fileName);
    }
}