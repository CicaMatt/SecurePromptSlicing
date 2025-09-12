import java.io.FileInputStream;
import java.io.IOException;

public class FileChecksumCalculator {
    public static void main(String[] args) {
        String filePath = "example.txt"; // Change this to your file path
        byte[] buffer = new byte[1024];
        int bytesRead = 0;
        int checksum = 0;

        try (FileInputStream fis = new FileInputStream(filePath)) {
            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (checksum == 0 && bytesRead == 0) {
            System.out.println("The buffer is empty.");
        } else {
            System.out.println("Number of bytes read: " + bytesRead);
            System.out.println("Checksum: " + checksum);
        }
    }
}