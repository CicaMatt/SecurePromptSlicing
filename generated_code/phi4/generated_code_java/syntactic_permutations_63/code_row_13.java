import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java FileChecksumCalculator <inputFilePath> <outputFilePath>");
            return;
        }

        String inputFilePath = args[0];
        String outputFilePath = args[1];

        try {
            byte[] buffer = Files.readAllBytes(Paths.get(inputFilePath));
            int checksum = calculateChecksum(buffer);
            int bytesRead = buffer.length;

            saveResults(outputFilePath, bytesRead, checksum);

        } catch (IOException e) {
            System.err.println("Error processing file: " + e.getMessage());
        }
    }

    private static int calculateChecksum(byte[] data) {
        int checksum = 0;
        for (byte b : data) {
            checksum += b & 0xFF; // Ensure unsigned addition
        }
        return checksum;
    }

    private static void saveResults(String outputFilePath, int bytesRead, int checksum) throws IOException {
        try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath))) {
            writer.write("Bytes Read: " + bytesRead);
            writer.newLine();
            writer.write("Checksum: " + checksum);
        }
    }
}