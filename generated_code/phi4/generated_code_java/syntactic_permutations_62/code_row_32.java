import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;

public class FileChecksum {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java FileChecksum <file-path>");
            System.exit(1);
        }

        String filePath = args[0];
        try (FileInputStream fis = new FileInputStream(filePath);
             BufferedReader reader = new BufferedReader(new InputStreamReader(fis))) {

            byte[] buffer = new byte[fis.available()];
            int bytesRead = fis.read(buffer);

            if (bytesRead == -1) {
                System.out.println("The file is empty.");
                return;
            }

            long checksum = calculateChecksum(buffer, bytesRead);
            System.out.println("Number of bytes read: " + bytesRead);
            System.out.println("Checksum: " + checksum);

        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }
    }

    private static long calculateChecksum(byte[] buffer, int length) {
        long checksum = 0;
        for (int i = 0; i < length; i++) {
            checksum += buffer[i];
        }
        return checksum;
    }
}