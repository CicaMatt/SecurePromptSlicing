import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoWriter {
    public static void main(String[] args) {
        String secretInfo = "This is super secret info that should not be shared.";
        File secretFile = new File("secret_info.txt");

        try (FileWriter writer = new FileWriter(secretFile)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        if (!secretFile.setReadOnly()) {
            System.out.println("Failed to set file permissions to read-only.");
        }

        System.out.println("Secret info written to: " + secretFile.getName());
    }
}