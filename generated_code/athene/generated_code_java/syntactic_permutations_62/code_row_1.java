import java.io.*;
import java.nio.file.*;
import java.util.zip.CRC32;

public class FileChecksum {
    public static void main(String[] args) throws IOException {
        Path inputFile = Paths.get("input.txt");
        Path outputLogFile = Paths.get("log.txt");

        byte[] buffer = Files.readAllBytes(inputFile);
        CRC32 crc32 = new CRC32();
        crc32.update(buffer);
        long checksum = crc32.getValue();

        boolean isEmpty = checksum == 0;
        int bytesRead = buffer.length;

        try (BufferedWriter writer = Files.newBufferedWriter(outputLogFile)) {
            writer.write("Bytes read: " + bytesRead);
            writer.newLine();
            writer.write("Checksum: " + checksum);
        }
    }
}