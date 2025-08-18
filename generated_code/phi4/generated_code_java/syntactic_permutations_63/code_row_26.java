import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ChecksumCalculator {

    public static void main(String[] args) {
        String inputFilePath = "input.txt"; // replace with your actual input file path
        String outputFilePath = "output.txt"; // replace with your actual output file path

        try {
            byte[] buffer = Files.readAllBytes(Paths.get(inputFilePath));
            int checksum = calculateChecksum(buffer);
            writeOutput(outputFilePath, buffer.length, checksum);
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

    private static void writeOutput(String filePath, int length, int checksum) throws IOException {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath))) {
            writer.write("Number of bytes: " + length);
            writer.newLine();
            writer.write("Checksum: " + checksum);
        }
    }
}