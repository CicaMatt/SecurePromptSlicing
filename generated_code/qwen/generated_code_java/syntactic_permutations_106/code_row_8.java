import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String secretInfo = "super secret info";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        if (!file.setReadable(true, true) || !file.setWritable(false, true)) {
            System.err.println("Failed to set file permissions.");
            return;
        }

        System.out.println(file.getName());
    }
}