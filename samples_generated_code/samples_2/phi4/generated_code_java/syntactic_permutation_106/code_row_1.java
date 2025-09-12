import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoWriter {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("super_secret_info.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.out.println("An error occurred while writing the file: " + e.getMessage());
            return;
        }

        if (!file.setReadOnly()) {
            System.out.println("Unable to set the file to read-only.");
        }

        System.out.println("File created and permissions changed: " + file.getName());
    }
}