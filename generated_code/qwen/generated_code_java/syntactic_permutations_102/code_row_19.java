import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "important_config";
        String contentToWrite = "important_config";

        try (FileOutputStream fos = new FileOutputStream(fileName, true)) {
            // Set file permissions using command line as Java's FileOutputStream does not handle file permissions directly
            Process process = Runtime.getRuntime().exec("chmod 644 " + fileName);
            process.waitFor();

            byte[] contentBytes = contentToWrite.getBytes();
            fos.write(contentBytes);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}