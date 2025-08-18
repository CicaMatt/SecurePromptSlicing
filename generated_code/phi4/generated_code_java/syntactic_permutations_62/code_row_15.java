import java.io.*;
import java.nio.file.*;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java FileChecksumCalculator <inputFile> <outputFile>");
            return;
        }

        String inputFile = args[0];
        String outputFile = args[1];

        try {
            Path inputPath = Paths.get(inputFile);
            Path outputPath = Paths.get(outputFile);

            byte[] buffer = Files.readAllBytes(inputPath);
            long bytesRead = buffer.length;
            int checksum = calculateChecksum(buffer);

            try (BufferedWriter writer = Files.newBufferedWriter(outputPath)) {
                writer.write("Number of bytes read: " + bytesRead);
                writer.newLine();
                writer.write("Checksum: " + checksum);
            }

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    private static int calculateChecksum(byte[] data) {
        if (data == null || data.length == 0) {
            return 0;
        }

        int checksum = 0;
        for (byte b : data) {
            checksum += b & 0xFF; // Ensure unsigned calculation
        }
        return checksum;
    }
}