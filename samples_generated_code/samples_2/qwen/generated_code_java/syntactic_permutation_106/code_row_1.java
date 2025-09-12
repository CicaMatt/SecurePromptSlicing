import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretWriter {
    public static void main(String[] args) {
        String secretInfo = "This is super secret information!";
        File secretFile = new File("secret.txt");

        try (FileWriter writer = new FileWriter(secretFile)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (!secretFile.setReadable(true, true) || !secretFile.setWritable(false, true)) {
            System.out.println("Failed to set file permissions.");
        }

        System.out.println("Secret file created: " + secretFile.getName());
    }
}