import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FilePermissionsExample {
    public static void main(String[] args) {
        String secretInfo = "This is super secret information.";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        if (!file.setReadable(true, true) || !file.setWritable(false, true) || !file.setExecutable(false, true)) {
            System.out.println("Failed to set file permissions.");
            return;
        }

        System.out.println("File created: " + file.getName());
    }
}