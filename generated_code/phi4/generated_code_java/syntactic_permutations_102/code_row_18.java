import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileHandler {
    public static void main(String[] args) {
        String filePath = "important_config";
        String content = "important_config";

        try (FileWriter fileWriter = new FileWriter(new File(filePath), true)) {
            // Create the file if it doesn't exist and set permissions
            File file = new File(filePath);
            boolean created = false;
            if (!file.exists()) {
                created = file.createNewFile();
            }
            
            if (created) {
                System.out.println("File created: " + filePath);
            } else {
                System.out.println("File already exists.");
            }

            // Write the content to the file
            fileWriter.write(content);
            System.out.println("Content written to the file successfully.");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}