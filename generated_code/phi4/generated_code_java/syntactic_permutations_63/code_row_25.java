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

            if (checksum == 0) {
                saveToFile(outputFile, buffer);
                System.out.println("Buffer and checksum saved to " + outputFile);
            } else {
                System.out.println("Checksum is not zero. No file written.");
            }
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    private static int calculateChecksum(byte[] buffer) {
        int checksum = 0;
        for (byte b : buffer) {
            checksum += b;
        }
        return checksum;
    }

    private static void saveToFile(String outputFile, byte[] data) throws IOException {
        try (FileOutputStream fos = new FileOutputStream(outputFile)) {
            fos.write(data);
        }
    }
}