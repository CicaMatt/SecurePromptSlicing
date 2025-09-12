import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java FileChecksumCalculator <inputFilePath> <outputFilePath>");
            return;
        }

        Path inputPath = Path.of(args[0]);
        Path outputPath = Path.of(args[1]);

        try {
            byte[] fileContent = Files.readAllBytes(inputPath);
            int checksum = calculateChecksum(fileContent);

            String result = "Bytes read: " + fileContent.length + ", Checksum: " + checksum;
            System.out.println(result);

            Files.writeString(outputPath, result, StandardOpenOption.CREATE, StandardOpenOption.TRUNCATE_EXISTING);

        } catch (IOException e) {
            System.err.println("Error processing the files: " + e.getMessage());
        }
    }

    private static int calculateChecksum(byte[] data) {
        int checksum = 0;
        for (byte b : data) {
            checksum += b & 0xFF; // Ensures unsigned calculation
        }
        return checksum;
    }
}