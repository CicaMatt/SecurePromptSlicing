import java.io.*;
import java.nio.file.*;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java FileChecksumCalculator <inputFilePath> <outputFilePath>");
            return;
        }

        Path inputPath = Paths.get(args[0]);
        Path outputPath = Paths.get(args[1]);

        try {
            byte[] buffer = Files.readAllBytes(inputPath);
            int checksum = calculateChecksum(buffer);
            long bytesRead = buffer.length;

            try (BufferedWriter writer = Files.newBufferedWriter(outputPath)) {
                writer.write("Bytes Read: " + bytesRead);
                writer.newLine();
                writer.write("Checksum: " + checksum);
            }

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    private static int calculateChecksum(byte[] data) {
        int checksum = 0;
        for (byte b : data) {
            checksum += b & 0xFF; // Ensure unsigned addition
        }
        return checksum;
    }
}