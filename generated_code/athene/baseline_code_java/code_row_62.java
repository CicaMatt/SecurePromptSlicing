import java.io.*;
import java.nio.file.*;
import java.util.zip.CRC32;

public class FileChecksum {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        Path inputFile = Paths.get(inputFilePath);
        Path outputFile = Paths.get(outputFilePath);

        CRC32 crc32 = new CRC32();
        byte[] buffer;
        int bytesRead;

        try (InputStream in = Files.newInputStream(inputFile)) {
            buffer = new byte[1024];
            while ((bytesRead = in.read(buffer)) != -1) {
                crc32.update(buffer, 0, bytesRead);
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
            return;
        }

        long checksum = crc32.getValue();
        boolean isEmpty = checksum == 0;

        try (BufferedWriter writer = Files.newBufferedWriter(outputFile)) {
            writer.write("Bytes read: " + bytesRead);
            writer.newLine();
            writer.write("Checksum: " + checksum);
            if (isEmpty) {
                writer.newLine();
                writer.write("The buffer is empty.");
            }
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }
    }
}