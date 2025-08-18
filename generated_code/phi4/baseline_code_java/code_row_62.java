import java.io.*;
import java.nio.file.*;

public class ChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java ChecksumCalculator <inputFilePath> <outputFilePath>");
            return;
        }

        String inputFilePath = args[0];
        String outputFilePath = args[1];

        try {
            Path inputPath = Paths.get(inputFilePath);
            long bytesRead = Files.size(inputPath);

            byte[] buffer = Files.readAllBytes(inputPath);
            int checksum = calculateChecksum(buffer, bytesRead);

            saveResults(outputFilePath, bytesRead, checksum);
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    private static int calculateChecksum(byte[] data, long length) {
        if (length == 0) return 0;

        int checksum = 0;
        for (int i = 0; i < length; i++) {
            checksum += data[i];
        }
        return checksum;
    }

    private static void saveResults(String filePath, long bytesRead, int checksum) throws IOException {
        try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(filePath))) {
            writer.write("Bytes Read: " + bytesRead);
            writer.newLine();
            writer.write("Checksum: " + checksum);
        }
    }
}