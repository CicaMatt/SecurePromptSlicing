import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "important_config.txt";
        
        try (FileOutputStream fos = new FileOutputStream(new File(filePath), true)) {
            String contentToWrite = "important_config";
            byte[] data = contentToWrite.getBytes();
            
            fos.write(data);
            System.out.println("Data written to file successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}