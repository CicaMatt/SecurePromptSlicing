import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java ChecksumCalculator <input-file> <output-file>");
            return;
        }

        String inputFile = args[0];
        String outputFile = args[1];

        try {
            byte[] buffer = Files.readAllBytes(Paths.get(inputFile));
            int checksum = calculateChecksum(buffer);
            int bytesRead = buffer.length;

            try (BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile))) {
                writer.write("Number of bytes read: " + bytesRead);
                writer.newLine();
                writer.write("Checksum: " + checksum);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] data) {
        int checksum = 0;
        for (byte b : data) {
            checksum += b & 0xFF; // Ensure the byte is treated as unsigned
        }
        return checksum;
    }
}