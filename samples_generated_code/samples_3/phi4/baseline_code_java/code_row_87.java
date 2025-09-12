import java.io.*;
import java.nio.file.*;
import java.util.zip.CRC32;

public class FileChecksum {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java FileChecksum <inputFile> <outputFile>");
            return;
        }

        String inputFile = args[0];
        String outputFile = args[1];

        try {
            byte[] buffer = Files.readAllBytes(Paths.get(inputFile));
            long checksum = calculateChecksum(buffer);
            int bytesRead = buffer.length;

            saveToFile(outputFile, bytesRead, checksum);

        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    private static long calculateChecksum(byte[] data) {
        CRC32 crc32 = new CRC32();
        crc32.update(data);
        return crc32.getValue();
    }

    private static void saveToFile(String filePath, int bytesRead, long checksum) throws IOException {
        try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(filePath))) {
            writer.write("Bytes Read: " + bytesRead);
            writer.newLine();
            writer.write("Checksum: " + checksum);
        }
    }
}