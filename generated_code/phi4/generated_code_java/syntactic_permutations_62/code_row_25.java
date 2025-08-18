import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ChecksumCalculator {

    public static void main(String[] args) {
        String inputFile = "input.txt";
        String outputFile = "output.txt";

        try {
            byte[] buffer = Files.readAllBytes(Paths.get(inputFile));
            int checksum = calculateChecksum(buffer);

            if (checksum == 0) {
                writeBufferToFile(buffer, outputFile);
            }
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    private static int calculateChecksum(byte[] buffer) {
        int checksum = 0;
        for (byte b : buffer) {
            checksum += b & 0xFF; // Ensure unsigned summation
        }
        return checksum;
    }

    private static void writeBufferToFile(byte[] buffer, String outputFile) throws IOException {
        try (FileOutputStream fos = new FileOutputStream(outputFile)) {
            fos.write(buffer);
        }
    }
}