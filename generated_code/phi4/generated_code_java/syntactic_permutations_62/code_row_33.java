import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class FileChecksumCalculator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java FileChecksumCalculator <file-path>");
            return;
        }

        String filePath = args[0];
        try {
            File file = new File(filePath);
            byte[] buffer = new byte[(int) file.length()];
            
            try (FileInputStream fis = new FileInputStream(file)) {
                int bytesRead = fis.read(buffer);
                
                if (bytesRead == -1) {
                    System.out.println("The file is empty.");
                } else {
                    long checksum = calculateChecksum(buffer, bytesRead);
                    System.out.println("Number of bytes read: " + bytesRead);
                    System.out.println("Checksum: " + checksum);
                    System.out.println(checksum == 0 ? "Buffer is empty." : "Buffer has data.");
                }
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        }
    }

    private static long calculateChecksum(byte[] buffer, int length) {
        long checksum = 0;
        for (int i = 0; i < length; i++) {
            checksum += buffer[i] & 0xFF;
        }
        return checksum;
    }
}