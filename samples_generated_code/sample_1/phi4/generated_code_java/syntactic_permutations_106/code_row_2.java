import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SuperSecretInfo {
    public static void main(String[] args) {
        String fileName = "super_secret_info.txt";
        String superSecretInfo = "This is some super secret info.";

        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(superSecretInfo);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
            return;
        }

        File file = new File(fileName);

        if (!file.setReadable(true, false) || !file.setWritable(false, false) || !file.setExecutable(true, false)) {
            System.err.println("Failed to set file permissions.");
            return;
        }

        System.out.println("File name: " + fileName);
    }
}