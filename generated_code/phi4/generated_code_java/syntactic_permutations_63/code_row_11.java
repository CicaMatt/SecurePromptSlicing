import java.io.*;
import java.nio.file.*;

public class FileChecksum {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java FileChecksum <input-file> <output-file>");
            return;
        }

        String inputFile = args[0];
        String outputFile = args[1];

        Path inputPath = Paths.get(inputFile);
        Path outputPath = Paths.get(outputFile);

        try (InputStream inputStream = Files.newInputStream(inputPath)) {
            byte[] buffer = new byte[8192]; // Buffer size of 8KB
            int bytesRead;
            long totalBytesRead = 0;

            // Calculate checksum and count bytes read
            int checksum = 0;
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
                totalBytesRead += bytesRead;
            }

            // Prepare output data
            String result = "Number of bytes read: " + totalBytesRead +
                            "\nChecksum: " + checksum;

            // Write to output file
            try (BufferedWriter writer = Files.newBufferedWriter(outputPath)) {
                writer.write(result);
            }
        } catch (IOException e) {
            System.err.println("I/O Error: " + e.getMessage());
        }
    }
}