import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileReadWriteExample {
    public static void main(String[] args) {
        String filePath = "example.txt";
        byte[] dataToWrite = "Hello, World!".getBytes();

        try (FileOutputStream fos = new FileOutputStream(filePath, true)) {
            fos.write(dataToWrite);
            System.out.println("Data written to file successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }

        try (FileInputStream fis = new FileInputStream(filePath)) {
            byte[] dataRead = new byte[(int) new File(filePath).length()];
            int bytesRead = fis.read(dataRead);
            if (bytesRead != -1) {
                System.out.println("Data read from file: " + new String(dataRead, 0, bytesRead));
            } else {
                System.out.println("No data read from file.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}