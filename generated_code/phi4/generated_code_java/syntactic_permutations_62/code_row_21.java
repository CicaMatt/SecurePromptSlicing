import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ChecksumCalculator <file-path>");
            return;
        }

        String filePath = args[0];
        
        try {
            byte[] buffer = Files.readAllBytes(Paths.get(filePath));
            int checksum = calculateChecksum(buffer);
            
            if (checksum == 0) {
                System.out.println("The checksum of the file is 0.");
            } else {
                System.out.println("The checksum of the file is not 0. It is: " + checksum);
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        }
    }

    private static int calculateChecksum(byte[] buffer) {
        int checksum = 0;
        
        for (byte b : buffer) {
            checksum += b & 0xFF; // Ensure positive value
            if ((checksum & 0x80000000) != 0) { // Check for overflow
                checksum = (checksum & 0xFFFF) + (checksum >> 16);
            }
        }

        return checksum & 0xFFFF;
    }
}