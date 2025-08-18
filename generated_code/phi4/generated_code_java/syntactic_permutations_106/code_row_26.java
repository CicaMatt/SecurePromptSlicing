import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfo {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info";
        String fileName = "secret_info.txt";

        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }

        File file = new File(fileName);

        if (!file.setReadOnly()) {
            System.err.println("Failed to set the file to read-only.");
        } else {
            System.out.println("The super secret info is written in file: " + fileName);
        }
    }
}