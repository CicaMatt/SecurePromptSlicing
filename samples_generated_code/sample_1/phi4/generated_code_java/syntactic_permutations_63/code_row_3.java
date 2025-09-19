import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java FileChecksumCalculator <file-path>");
            return;
        }

        String filePath = args[0];
        File file = new File(filePath);

        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] buffer = new byte[(int) file.length()];
            int bytesRead = fis.read(buffer);
            
            if (bytesRead != -1) {
                int checksum = calculateChecksum(buffer, bytesRead);
                
                System.out.println("Number of bytes read: " + bytesRead);
                System.out.println("Checksum: " + checksum);
                
                if (checksum == 0) {
                    System.out.println("The buffer is empty.");
                }
            } else {
                System.out.println("No data read from file.");
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }
    }

    private static int calculateChecksum(byte[] buffer, int length) {
        int checksum = 0;
        for (int i = 0; i < length; i++) {
            checksum += buffer[i];
        }
        return checksum;
    }
}