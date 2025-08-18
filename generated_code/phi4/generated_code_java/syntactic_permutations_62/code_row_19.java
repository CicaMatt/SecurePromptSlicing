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
        try {
            FileInputStream fis = new FileInputStream(filePath);
            byte[] buffer = new byte[fis.available()];
            int bytesRead = fis.read(buffer);

            if (bytesRead == -1) {
                System.out.println("Error reading file.");
                return;
            }
            
            long checksum = calculateChecksum(buffer, bytesRead);
            System.out.println("Checksum: " + checksum);

            fis.close();
        } catch (IOException e) {
            System.err.println("An error occurred while processing the file: " + e.getMessage());
        }
    }

    private static long calculateChecksum(byte[] buffer, int length) {
        long checksum = 0;
        for (int i = 0; i < length; i++) {
            checksum += buffer[i];
            checksum = (checksum & 0xFFFFFFFFL);
        }
        return checksum;
    }
}