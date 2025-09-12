import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileCreator {
    public static void main(String[] args) {
        String content = ".";
        String fileName = "secret.txt";
        
        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(content);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        File file = new File(fileName);
        boolean isReadOnlySet = file.setReadOnly();
        
        if (isReadOnlySet) {
            System.out.println("File permissions changed to read-only for the owner.");
        } else {
            System.out.println("Failed to change file permissions.");
        }
        
        System.out.println("File created: " + fileName);
    }
}