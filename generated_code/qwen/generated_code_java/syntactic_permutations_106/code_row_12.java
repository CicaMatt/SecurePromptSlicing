import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileWriter {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
            System.out.println("File name: " + file.getName());
        } catch (IOException e) {
            e.printStackTrace();
        }

        boolean success = file.setReadOnly();
        if (!success) {
            System.err.println("Failed to set the file read-only.");
        }
    }
}