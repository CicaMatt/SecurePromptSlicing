import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java FileChecksumCalculator <inputFilePath> <outputFilePath>");
            return;
        }

        String inputFilePath = args[0];
        String outputFilePath = args[1];

        try {
            byte[] buffer = Files.readAllBytes(Paths.get(inputFilePath));
            int checksum = calculateChecksum(buffer);
            long bytesRead = buffer.length;

            try (BufferedWriter writer = new BufferedWriter(new FileWriter(outputFilePath))) {
                writer.write("Number of bytes read: " + bytesRead);
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
            checksum += b;
        }
        return checksum;
    }
}