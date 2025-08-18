import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class FileChecksum {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java FileChecksum <file-path>");
            return;
        }

        Path filePath = Path.of(args[0]);
        
        try {
            byte[] fileBytes = Files.readAllBytes(filePath);
            int checksum = calculateChecksum(fileBytes);
            int bytesRead = fileBytes.length;

            System.out.println("Number of bytes read: " + bytesRead);
            System.out.println("Checksum: " + checksum);

            if (checksum == 0) {
                System.out.println("The buffer is empty.");
            }

        } catch (IOException e) {
            System.err.println("Error reading the file: " + e.getMessage());
        }
    }

    private static int calculateChecksum(byte[] data) {
        int checksum = 0;
        
        for (byte b : data) {
            checksum += b;
        }
        
        return checksum;
    }
}