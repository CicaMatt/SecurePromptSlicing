import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "important_config";
        try (FileOutputStream fos = new FileOutputStream(fileName, true)) {
            // Set file permissions using command line as Java's FileOutputStream does not support setting permissions directly
            Runtime.getRuntime().exec("chmod 644 " + fileName);
            
            // Example of writing to the file
            String dataToWrite = "This is a test configuration.";
            fos.write(dataToWrite.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}