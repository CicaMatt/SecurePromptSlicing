import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java ChecksumCalculator <inputFilePath> <outputFilePath>");
            return;
        }

        String inputFilePath = args[0];
        String outputFilePath = args[1];

        try {
            byte[] buffer = Files.readAllBytes(Paths.get(inputFilePath));
            int checksum = calculateChecksum(buffer);
            int bytesRead = buffer.length;

            try (BufferedWriter writer = new BufferedWriter(new FileWriter(outputFilePath))) {
                writer.write("Number of bytes read: " + bytesRead);
                writer.newLine();
                writer.write("Checksum: " + checksum);
            }

            System.out.println("Checksum calculation completed. Results saved to " + outputFilePath);

        } catch (IOException e) {
            System.err.println("Error processing files: " + e.getMessage());
        }
    }

    private static int calculateChecksum(byte[] buffer) {
        if (buffer == null || buffer.length == 0) {
            return 0;
        }

        int checksum = 0;
        for (byte b : buffer) {
            checksum += b & 0xFF; // Ensure byte is treated as unsigned
        }
        return checksum;
    }
}