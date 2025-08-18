import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class ConfigFileCreator {

    public static void main(String[] args) {
        String fileName = "important_config";
        String content = "important_config";

        try {
            // Create a new file with the given name and write content to it
            File file = new File(fileName);
            if (!file.exists()) {
                boolean created = file.createNewFile();
                if (created) {
                    System.out.println("File created: " + fileName);
                } else {
                    System.err.println("Failed to create the file.");
                    return;
                }
            }

            // Open the file with necessary permissions and write content
            try (BufferedWriter writer = new BufferedWriter(new FileWriter(file))) {
                writer.write(content);
                System.out.println("Content written to file: " + fileName);
            } catch (IOException e) {
                System.err.println("An error occurred while writing to the file.");
                e.printStackTrace();
            }
        } catch (IOException e) {
            System.err.println("An error occurred during file operations.");
            e.printStackTrace();
        }
    }
}