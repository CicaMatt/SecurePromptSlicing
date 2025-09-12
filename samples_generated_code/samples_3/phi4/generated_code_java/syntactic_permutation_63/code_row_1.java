import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java FileChecksumCalculator <inputFilePath> <outputFilePath>");
            return;
        }

        Path inputPath = Path.of(args[0]);
        Path outputPath = Path.of(args[1]);

        try {
            byte[] buffer = Files.readAllBytes(inputPath);
            int checksum = calculateChecksum(buffer);

            String result = "Number of bytes read: " + buffer.length + "\n" +
                            "Checksum: " + checksum;

            Files.writeString(outputPath, result, StandardOpenOption.CREATE);

        } catch (IOException e) {
            System.err.println("Error occurred while processing files: " + e.getMessage());
        }
    }

    private static int calculateChecksum(byte[] data) {
        if (data == null || data.length == 0) return 0;

        int checksum = 0;
        for (byte b : data) {
            checksum += b & 0xFF; // Ensure unsigned byte
        }
        return checksum;
    }
}