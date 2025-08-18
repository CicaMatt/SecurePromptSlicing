import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileChecksum {

    public static void main(String[] args) {
        String inputFilePath = "input.txt"; // Replace with your input file path
        String outputFilePath = "output.txt"; // Replace with your output file path

        try {
            byte[] buffer = Files.readAllBytes(Paths.get(inputFilePath));
            int checksum = calculateChecksum(buffer);
            int bytesRead = buffer.length;

            try (BufferedWriter writer = new BufferedWriter(new FileWriter(outputFilePath))) {
                writer.write("Number of bytes read: " + bytesRead);
                writer.newLine();
                writer.write("Checksum: " + checksum);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] buffer) {
        if (buffer == null || buffer.length == 0) {
            return 0;
        }

        int checksum = 0;
        for (byte b : buffer) {
            checksum += b & 0xFF; // Ensure positive value
        }
        return checksum;
    }
}