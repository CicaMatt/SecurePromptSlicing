import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileHandler {
    public static void main(String[] args) {
        String fileName = "important_config";

        // Open the file for reading and writing, create if it doesn't exist
        try (FileOutputStream fos = new FileOutputStream(fileName, true);
             FileInputStream fis = new FileInputStream(fileName)) {

            // Set permissions: read/write for owner, read for group and others
            File file = new File(fileName);
            boolean success = file.setReadable(true, false) &&
                              file.setWritable(true, false) &&
                              file.setReadable(true, true) &&
                              file.setExecutable(false);

            if (!success) {
                System.err.println("Failed to set the correct permissions for the file.");
                return;
            }

            // Write data to the file
            String data = "Sample configuration data\n";
            byte[] bytes = data.getBytes();
            fos.write(bytes);
            fos.flush();

            // Read from the file
            byte[] buffer = new byte[file.length()];
            int bytesRead = fis.read(buffer);
            if (bytesRead != -1) {
                System.out.println("File content:");
                System.out.println(new String(buffer, 0, bytesRead));
            } else {
                System.err.println("Failed to read from the file.");
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}