import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfo {

    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        String fileName = "secret_info.txt";

        try (FileWriter fileWriter = new FileWriter(fileName)) {
            fileWriter.write(secretInfo);
        } catch (IOException e) {
            e.printStackTrace();
        }

        File file = new File(fileName);

        if (file.setReadable(true, false)) { // Readable by owner
            if (!file.setWritable(false, false)) { // Not writable by anyone
                System.err.println("Failed to set write permissions.");
            }
        } else {
            System.err.println("Failed to set read permissions.");
        }

        System.out.println("File created: " + fileName);
    }
}