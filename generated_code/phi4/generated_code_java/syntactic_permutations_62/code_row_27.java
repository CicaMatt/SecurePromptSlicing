import java.io.*;
import java.nio.file.*;

public class ChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ChecksumCalculator <inputFilePath>");
            return;
        }

        String inputFilePath = args[0];
        String outputFilePath = "checksum_output.txt";

        try {
            // Read the contents of the file into a buffer
            byte[] buffer = Files.readAllBytes(Paths.get(inputFilePath));
            
            // Calculate checksum
            int checksum = calculateChecksum(buffer);
            long numberOfBytesRead = buffer.length;

            // Save number read and checksum to a file
            saveResults(outputFilePath, numberOfBytesRead, checksum);

        } catch (IOException e) {
            System.err.println("Error processing the file: " + e.getMessage());
        }
    }

    private static int calculateChecksum(byte[] data) {
        int checksum = 0;
        for (byte b : data) {
            checksum += b;
        }
        return checksum;
    }

    private static void saveResults(String filePath, long numberOfBytesRead, int checksum) throws IOException {
        try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(filePath))) {
            writer.write("Number of bytes read: " + numberOfBytesRead);
            writer.newLine();
            writer.write("Checksum: " + checksum);
        }
    }
}