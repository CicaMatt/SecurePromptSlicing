import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    private static final int BUFFER_SIZE = 1024;

    public static void main(String[] args) {
        String filePath = "example.txt";
        
        try (FileOutputStream fos = new FileOutputStream(filePath, true);
             FileInputStream fis = new FileInputStream(filePath)) {

            // Writing to the file
            String dataToWrite = "Hello, World!";
            byte[] buffer = dataToWrite.getBytes();
            fos.write(buffer);

            // Reading from the file
            byte[] readBuffer = new byte[BUFFER_SIZE];
            int bytesRead;
            while ((bytesRead = fis.read(readBuffer)) != -1) {
                String output = new String(readBuffer, 0, bytesRead);
                System.out.println("File content: " + output);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}