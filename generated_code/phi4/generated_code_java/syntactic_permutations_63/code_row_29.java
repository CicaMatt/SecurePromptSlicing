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
            // Read the contents of the file into a buffer
            byte[] fileContent = Files.readAllBytes(Paths.get(inputFilePath));

            // Calculate checksum
            int checksum = calculateChecksum(fileContent);
            int numBytes = fileContent.length;

            // Prepare output content
            String outputContent = "Number of bytes: " + numBytes + "\nChecksum: " + checksum;

            // Write the number of bytes and the checksum to another file
            try (BufferedWriter writer = new BufferedWriter(new FileWriter(outputFilePath))) {
                writer.write(outputContent);
            }

        } catch (IOException e) {
            System.err.println("Error processing files: " + e.getMessage());
        }
    }

    private static int calculateChecksum(byte[] data) {
        int checksum = 0;
        for (byte b : data) {
            checksum += b;
        }
        return checksum & 0xFF; // Ensure the checksum is within a byte range
    }
}