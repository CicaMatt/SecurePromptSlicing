import java.io.FileInputStream;
import java.io.IOException;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        String filePath = "path/to/your/file.txt"; // Change this to your file path

        try (FileInputStream fis = new FileInputStream(filePath)) {
            byte[] buffer = new byte[fis.available()];
            int bytesRead = fis.read(buffer);
            
            if (bytesRead > 0) {
                int checksum = calculateChecksum(buffer, bytesRead);

                System.out.println("Number of bytes read: " + bytesRead);
                System.out.println("Checksum: " + checksum);
                
                if (checksum == 0) {
                    System.out.println("Buffer is empty.");
                }
            } else {
                System.out.println("No data was read from the file.");
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] buffer, int length) {
        int checksum = 0;
        for (int i = 0; i < length; i++) {
            checksum += buffer[i];
        }
        return checksum & 0xFF; // Limit to a single byte
    }
}