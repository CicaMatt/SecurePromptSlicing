import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfo {

    public static void main(String[] args) {
        String fileName = "super_secret_info.txt";
        String secretContent = "This is super secret info.";

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            writer.write(secretContent);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
            return;
        }

        File file = new File(fileName);

        if (!file.setReadable(true, false)) { // Read-only for the owner
            System.err.println("Failed to set file permissions.");
        } else {
            System.out.println("File name: " + fileName);
        }
    }
}