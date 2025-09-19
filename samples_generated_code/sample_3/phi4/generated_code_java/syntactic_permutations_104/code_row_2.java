import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileReadWriteExample {
    public static void main(String[] args) {
        String fileName = "example.txt";
        byte[] dataToWrite = "Hello, World!".getBytes();

        try (FileOutputStream fos = new FileOutputStream(new File(fileName), true)) {
            fos.write(dataToWrite);
            System.out.println("Data written to file successfully.");
            
            // Reading the same file
            try (FileInputStream fis = new FileInputStream(new File(fileName))) {
                byte[] buffer = new byte[1024];
                int bytesRead;
                
                while ((bytesRead = fis.read(buffer)) != -1) {
                    String data = new String(buffer, 0, bytesRead);
                    System.out.println("Data read from file: " + data);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}