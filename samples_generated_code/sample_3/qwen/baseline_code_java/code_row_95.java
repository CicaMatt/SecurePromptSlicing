import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoWriter {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File secretFile = new File("secret_info.txt");

        try (FileWriter writer = new FileWriter(secretFile)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        if (!secretFile.setReadable(true, true) || !secretFile.setWritable(false, true)) {
            System.out.println("Failed to set file permissions.");
            return;
        }

        System.out.println("Secret information written to: " + secretFile.getName());
    }
}