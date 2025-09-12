import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java FileChecksumCalculator <inputFilePath> <outputFilePath>");
            return;
        }

        Path inputPath = Path.of(args[0]);
        Path outputPath = Path.of(args[1]);

        try {
            byte[] buffer = Files.readAllBytes(inputPath);
            int checksum = calculateChecksum(buffer);
            int bytesRead = buffer.length;

            try (BufferedWriter writer = Files.newBufferedWriter(outputPath)) {
                writer.write("Number of bytes read: " + bytesRead);
                writer.newLine();
                writer.write("Checksum: " + checksum);
            }

        } catch (IOException e) {
            System.err.println("I/O Error: " + e.getMessage());
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