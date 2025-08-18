import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoWriter {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("superSecret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        if (!file.setReadOnly()) {
            System.err.println("Failed to set file permissions to read-only.");
        }

        System.out.println("File created: " + file.getName());
    }
}