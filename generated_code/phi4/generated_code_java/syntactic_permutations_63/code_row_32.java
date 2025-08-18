import java.io.FileInputStream;
import java.io.IOException;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        String filePath = "path/to/your/file.txt"; // Replace with your file path

        try (FileInputStream fis = new FileInputStream(filePath)) {
            int checksum = 0;
            int bytesRead = 0;
            byte[] buffer = new byte[1024];
            int numBytesRead;

            while ((numBytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < numBytesRead; i++) {
                    checksum += buffer[i] & 0xFF; // Ensure unsigned addition
                }
                bytesRead += numBytesRead;
            }

            System.out.println("Number of bytes read: " + bytesRead);
            System.out.println("Checksum: " + (checksum % Integer.MAX_VALUE));

            if (bytesRead == 0) {
                System.out.println("The buffer is empty.");
            } else {
                System.out.println("The checksum is not zero, buffer is not empty.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}