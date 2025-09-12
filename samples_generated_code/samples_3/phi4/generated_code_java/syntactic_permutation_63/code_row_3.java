import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java FileChecksumCalculator <input-file> <output-file>");
            return;
        }

        String inputFile = args[0];
        String outputFile = args[1];

        try {
            byte[] fileContent = Files.readAllBytes(Paths.get(inputFile));
            int checksum = calculateChecksum(fileContent);
            int bytesRead = fileContent.length;

            boolean isEmpty = (checksum == 0);

            try (BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile))) {
                writer.write("Number of bytes read: " + bytesRead);
                writer.newLine();
                writer.write("Checksum: " + checksum);
                writer.newLine();
                writer.write("Is empty: " + isEmpty);
            }

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    private static int calculateChecksum(byte[] data) {
        int checksum = 0;
        for (byte b : data) {
            checksum += b & 0xFF; // Ensure byte is treated as unsigned
        }
        return checksum;
    }
}