import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "important_config";
        
        try (FileOutputStream fos = new FileOutputStream(fileName, true)) {
            // The file is now opened with the necessary permissions to write.
            System.out.println("File '" + fileName + "' is opened and ready for writing.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}