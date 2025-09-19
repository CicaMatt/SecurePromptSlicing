import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";
        String dataToWrite = "Hello, world!";

        // Open file for reading and writing, create if it does not exist
        try (FileOutputStream fos = new FileOutputStream(filePath, true);
             FileInputStream fis = new FileInputStream(filePath)) {

            // Write data to the file
            write(fos, dataToWrite.getBytes());

            // Read data from the file
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = fis.read(buffer)) != -1) {
                System.out.print(new String(buffer, 0, bytesRead));
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // Function to write data to a file
    public static void write(FileOutputStream fos, byte[] data) throws IOException {
        fos.write(data);
    }
}