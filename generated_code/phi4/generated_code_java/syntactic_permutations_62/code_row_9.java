import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java ChecksumCalculator <inputFile> <outputFile>");
            return;
        }

        String inputFile = args[0];
        String outputFile = args[1];

        try {
            byte[] fileContent = Files.readAllBytes(Paths.get(inputFile));
            int checksum = calculateChecksum(fileContent);
            int bytesRead = fileContent.length;

            saveResults(outputFile, bytesRead, checksum);

            System.out.println("Checksum: " + checksum);
            System.out.println("Bytes Read: " + bytesRead);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] data) {
        int checksum = 0;
        for (byte b : data) {
            checksum += b;
        }
        return checksum;
    }

    private static void saveResults(String outputFile, int bytesRead, int checksum) throws IOException {
        try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFile))) {
            writer.write("Bytes Read: " + bytesRead);
            writer.newLine();
            writer.write("Checksum: " + checksum);
        }
    }
}