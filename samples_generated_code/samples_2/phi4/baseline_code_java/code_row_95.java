import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileChecksum {

    public static void main(String[] args) {
        if (args.length < 2) {
            System.err.println("Usage: java FileChecksum <inputFile> <outputFile>");
            System.exit(1);
        }

        String inputFile = args[0];
        String outputFile = args[1];

        try {
            byte[] fileContent = Files.readAllBytes(Paths.get(inputFile));
            int checksum = calculateChecksum(fileContent);
            int bytesRead = fileContent.length;

            try (BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile))) {
                writer.write("Number of bytes read: " + bytesRead);
                writer.newLine();
                writer.write("Checksum: " + checksum);
            }

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
}