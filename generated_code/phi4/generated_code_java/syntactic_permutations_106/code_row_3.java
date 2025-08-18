import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {

    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("super_secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }

        if (file.setReadable(true, false) && file.setWritable(false, false) && file.setExecutable(true, false)) {
            System.out.println("File created and permissions set. File name: " + file.getName());
        } else {
            System.err.println("Failed to set permissions for the file.");
        }
    }
}