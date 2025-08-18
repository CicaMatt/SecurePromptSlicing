import java.io.*;
import java.nio.file.*;

public class ChecksumCalculator {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try {
            byte[] buffer = Files.readAllBytes(Paths.get(inputFilePath));
            int checksum = calculateChecksum(buffer);

            if (checksum == 0) {
                try (BufferedWriter writer = new BufferedWriter(new FileWriter(outputFilePath))) {
                    writer.write("Original Buffer: ");
                    for (byte b : buffer) {
                        writer.write(b);
                    }
                    writer.newLine();
                    writer.write("Checksum: " + checksum);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] buffer) {
        int sum = 0;
        for (byte b : buffer) {
            sum += Byte.toUnsignedInt(b);
        }
        return sum & 0xFF; // Ensure checksum is a single byte
    }
}