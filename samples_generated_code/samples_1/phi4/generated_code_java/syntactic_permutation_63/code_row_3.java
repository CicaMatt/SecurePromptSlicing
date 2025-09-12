import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide a file path as an argument.");
            return;
        }

        String filePath = args[0];
        calculateFileChecksum(filePath);
    }

    private static void calculateFileChecksum(String filePath) {
        File file = new File(filePath);
        
        if (!file.exists() || !file.isFile()) {
            System.out.println("The specified file does not exist or is not a regular file.");
            return;
        }
        
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] buffer = new byte[1024];
            int bytesRead;
            long totalBytesRead = 0;
            int checksum = 0;

            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
                totalBytesRead += bytesRead;
            }

            System.out.println("Total bytes read: " + totalBytesRead);
            System.out.println("Checksum: " + checksum);

            if (checksum == 0) {
                System.out.println("The buffer is empty.");
            }

        } catch (IOException e) {
            System.out.println("An error occurred while reading the file: " + e.getMessage());
        }
    }
}