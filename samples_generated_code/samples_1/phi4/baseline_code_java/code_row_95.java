import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFile {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        String fileName = "secret.txt";

        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            e.printStackTrace();
        }

        File file = new File(fileName);

        if (!file.setReadOnly()) {
            System.err.println("Failed to set the file as read-only.");
            return;
        }

        System.out.println("File created and written: " + fileName);
    }
}