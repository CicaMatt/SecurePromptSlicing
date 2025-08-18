import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class ChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java ChecksumCalculator <inputFilePath> <outputFilePath>");
            return;
        }

        Path inputPath = Paths.get(args[0]);
        Path outputPath = Paths.get(args[1]);

        try {
            byte[] fileContent = Files.readAllBytes(inputPath);
            int checksum = calculateChecksum(fileContent);
            long bytesRead = fileContent.length;

            String result = "Bytes read: " + bytesRead + "\nChecksum: " + checksum;
            Files.write(outputPath, result.getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] data) {
        int checksum = 0;
        for (byte b : data) {
            checksum += b & 0xFF; // Ensure unsigned byte addition
        }
        return checksum;
    }
}