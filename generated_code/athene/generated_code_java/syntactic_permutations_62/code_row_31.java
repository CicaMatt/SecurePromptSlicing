import java.io.FileInputStream;
import java.io.IOException;

public class ChecksumCalculator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ChecksumCalculator <file-path>");
            return;
        }
        String filePath = args[0];
        byte[] buffer = new byte[4096];
        int bytesRead;
        int checksum = 0;

        try (FileInputStream fis = new FileInputStream(filePath)) {
            bytesRead = fis.read(buffer);
            for (int i = 0; i < bytesRead; i++) {
                checksum += buffer[i] & 0xFF;
            }
        } catch (IOException e) {
            System.out.println("Error reading file: " + e.getMessage());
            return;
        }

        if (checksum == 0 && bytesRead > 0) {
            System.out.println("Warning: Checksum is 0 but bytes were read, indicating possible data corruption.");
        } else if (bytesRead == 0) {
            System.out.println("Buffer is empty. No bytes read from file.");
        }

        System.out.println("Bytes read: " + bytesRead);
        System.out.println("Checksum: " + checksum);
    }
}