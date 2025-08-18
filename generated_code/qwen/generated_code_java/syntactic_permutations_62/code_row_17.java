import java.io.FileInputStream;
import java.io.IOException;

public class FileChecksumCalculator {
    public static void main(String[] args) {
        String filePath = "example.txt"; // Specify the path to your file here
        try (FileInputStream fis = new FileInputStream(filePath)) {
            int checksum = 0;
            int bytesRead;
            byte[] buffer = new byte[8192];
            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }
            System.out.println("Checksum: " + checksum);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}