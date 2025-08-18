import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileWriter {
    public static void main(String[] args) {
        String secretInfo = "This is super secret info that should not be shared.";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        if (!file.setReadOnly()) {
            System.err.println("Failed to set file to read-only.");
        }

        System.out.println("File created: " + file.getName());
    }
}