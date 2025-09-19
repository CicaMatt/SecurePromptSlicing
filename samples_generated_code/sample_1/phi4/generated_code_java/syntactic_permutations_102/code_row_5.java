import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "important_config";
        
        try (FileWriter fileWriter = new FileWriter(filePath, true)) {
            fileWriter.write("important_config\n");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}