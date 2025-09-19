import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class FileChecksum {
    public static void main(String[] args) throws IOException {
        if (args.length != 2) {
            System.err.println("Usage: java FileChecksum <inputFile> <outputFile>");
            return;
        }

        Path inputFilePath = Path.of(args[0]);
        Path outputFilePath = Path.of(args[1]);

        byte[] fileContent = Files.readAllBytes(inputFilePath);
        int checksum = calculateChecksum(fileContent);
        long bytesRead = fileContent.length;

        try (BufferedWriter writer = Files.newBufferedWriter(outputFilePath, StandardOpenOption.CREATE)) {
            writer.write("Number of bytes read: " + bytesRead);
            writer.newLine();
            writer.write("Checksum: " + checksum);
        }
    }

    private static int calculateChecksum(byte[] data) {
        if (data == null || data.length == 0) {
            return 0;
        }

        int checksum = 0;
        for (byte b : data) {
            checksum += b;
        }
        
        return checksum;
    }
}