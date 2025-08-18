import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ChecksumCalculator {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java ChecksumCalculator <inputFile> <outputFile>");
            System.exit(1);
        }

        String inputFile = args[0];
        String outputFile = args[1];

        try {
            byte[] buffer = Files.readAllBytes(Paths.get(inputFile));
            int checksum = 0;
            for (byte b : buffer) {
                checksum += b & 0xFF; // Ensure unsigned addition
            }

            int bytesRead = buffer.length;

            try (BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile))) {
                writer.write("Bytes Read: " + bytesRead);
                writer.newLine();
                writer.write("Checksum: " + checksum);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}