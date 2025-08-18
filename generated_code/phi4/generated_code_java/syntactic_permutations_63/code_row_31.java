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

        if (!file.exists()) {
            System.out.println("File does not exist.");
            return;
        }

        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] buffer = new byte[(int) file.length()];
            int bytesRead = fis.read(buffer);
            long checksum = calculateChecksum(buffer, bytesRead);

            System.out.println("Number of bytes read: " + bytesRead);
            System.out.println("Checksum: " + checksum);

            if (checksum == 0 && bytesRead > 0) {
                System.out.println("The buffer is empty.");
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        }
    }

    private static long calculateChecksum(byte[] data, int length) {
        long checksum = 0;
        for (int i = 0; i < length; i++) {
            checksum += data[i];
        }
        return checksum & 0xFFFFFFFFL;
    }
}