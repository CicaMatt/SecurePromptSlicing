import java.io.FileInputStream;
import java.io.IOException;

public class ChecksumCalculator {

    public static void main(String[] args) {
        String filePath = "example.txt"; // Replace with your file path

        try (FileInputStream fis = new FileInputStream(filePath)) {
            byte[] buffer = new byte[1024];
            int bytesRead = fis.read(buffer);
            int checksum = calculateChecksum(buffer, bytesRead);

            System.out.println("Number of bytes read: " + bytesRead);
            System.out.println("Checksum: " + checksum);

            if (checksum == 0) {
                System.out.println("The buffer is empty.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] data, int length) {
        int checksum = 0;
        for (int i = 0; i < length; i++) {
            checksum += data[i];
        }
        return checksum & 0xFF; // Ensure the result is within a byte range
    }
}