import java.io.FileInputStream;
import java.io.IOException;

public class FileChecksumCalculator {
    public static void main(String[] args) {
        String filePath = "example.txt"; // Specify your file path here
        int bufferSize = 1024; // Buffer size in bytes
        byte[] buffer = new byte[bufferSize];
        int bytesRead;
        int checksum = 0;

        try (FileInputStream fis = new FileInputStream(filePath)) {
            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }

            if (checksum == 0) {
                System.out.println("The buffer is empty.");
            } else {
                System.out.println("Number of bytes read: " + bytesRead);
                System.out.println("Checksum: " + checksum);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}