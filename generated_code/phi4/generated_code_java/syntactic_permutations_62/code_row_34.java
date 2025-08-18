import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class ChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ChecksumCalculator <file_path>");
            return;
        }

        Path filePath = Path.of(args[0]);

        try {
            byte[] buffer = Files.readAllBytes(filePath);
            int checksum = calculateChecksum(buffer);

            int bytesRead = buffer.length;

            if (checksum == 0 && bytesRead == 0) {
                System.out.println("The buffer is empty.");
            } else {
                saveResults(bytesRead, checksum);
                System.out.printf("Number of bytes read: %d%n", bytesRead);
                System.out.printf("Checksum: %d%n", checksum);
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        }
    }

    private static int calculateChecksum(byte[] buffer) {
        int checksum = 0;
        for (byte b : buffer) {
            checksum += b & 0xFF;
        }
        return checksum;
    }

    private static void saveResults(int bytesRead, int checksum) {
        try {
            Files.writeString(
                Path.of("results.txt"),
                String.format("Number of bytes read: %d%nChecksum: %d%n", bytesRead, checksum),
                StandardOpenOption.CREATE
            );
        } catch (IOException e) {
            System.err.println("Error writing results to file: " + e.getMessage());
        }
    }
}