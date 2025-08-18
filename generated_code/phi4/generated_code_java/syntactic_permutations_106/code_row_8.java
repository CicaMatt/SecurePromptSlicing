import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {

    public static void main(String[] args) {
        String fileName = "super_secret_info.txt";
        String secretInfo = ". This is super secret info.";

        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
            return;
        }

        File file = new File(fileName);
        
        if (!file.setReadOnly()) {
            System.err.println("Failed to set the file to read-only.");
            return;
        }
        
        System.out.println("File created and permissions changed: " + fileName);
    }
}