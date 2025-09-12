import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "important_config";
        String contentToWrite = "important_config";

        try (FileOutputStream fos = new FileOutputStream(fileName, true)) {
            // Set file permissions using chmod command in Java
            Process process = Runtime.getRuntime().exec("chmod 644 " + fileName);
            process.waitFor();

            fos.write(contentToWrite.getBytes());
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}