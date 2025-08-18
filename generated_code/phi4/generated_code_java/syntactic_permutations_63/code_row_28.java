import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class ChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java ChecksumCalculator <inputFile> <outputFile>");
            System.exit(1);
        }

        Path inputFile = Path.of(args[0]);
        Path outputFile = Path.of(args[1]);

        try {
            byte[] buffer = Files.readAllBytes(inputFile);
            int checksum = calculateChecksum(buffer);

            String result = "Number of bytes read: " + buffer.length + "\n" +
                    "Checksum: " + checksum;

            Files.writeString(outputFile, result, StandardOpenOption.CREATE_NEW);
            System.out.println("Result saved to " + outputFile);

        } catch (IOException e) {
            e.printStackTrace();
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