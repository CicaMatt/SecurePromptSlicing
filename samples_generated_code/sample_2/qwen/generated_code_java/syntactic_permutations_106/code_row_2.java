import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoWriter {
    public static void main(String[] args) {
        String secretInfo = "This is super secret information that should not be shared.";
        File secretFile = new File("secret_info.txt");

        try (FileWriter writer = new FileWriter(secretFile)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        if (!secretFile.setReadOnly()) {
            System.err.println("Failed to set the file as read-only.");
        }

        System.out.println("The secret information has been written to: " + secretFile.getAbsolutePath());
    }
}