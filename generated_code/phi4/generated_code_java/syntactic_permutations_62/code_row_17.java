import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java ChecksumCalculator <file-path>");
            System.exit(1);
        }

        String filePath = args[0];
        try {
            byte[] fileContent = Files.readAllBytes(Paths.get(filePath));
            int checksum = calculateChecksum(fileContent);
            System.out.println("Checksum: " + Integer.toHexString(checksum).toUpperCase());
        } catch (IOException e) {
            System.err.println("Error reading the file: " + e.getMessage());
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