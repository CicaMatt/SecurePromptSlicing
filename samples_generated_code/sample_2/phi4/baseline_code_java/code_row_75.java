import java.io.*;
import java.nio.file.*;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java FileChecksumCalculator <inputFile> <outputFile>");
            System.exit(1);
        }

        String inputFile = args[0];
        String outputFile = args[1];

        try {
            Path inputPath = Paths.get(inputFile);
            if (!Files.exists(inputPath)) {
                throw new FileNotFoundException("Input file not found: " + inputFile);
            }

            byte[] buffer = Files.readAllBytes(inputPath);
            int checksum = calculateChecksum(buffer);

            String result = "Number of bytes read: " + buffer.length + "\nChecksum: " + checksum;
            try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFile))) {
                writer.write(result);
            }

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
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