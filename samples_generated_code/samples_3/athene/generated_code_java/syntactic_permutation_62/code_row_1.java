import java.io.*;
import java.nio.file.*;
import java.util.zip.CRC32;

public class ChecksumWriter {
    public static void main(String[] args) {
        Path inputPath = Paths.get("input.dat");
        Path outputPath = Paths.get("output.txt");

        byte[] buffer = new byte[1024];
        int bytesRead;
        CRC32 crc32 = new CRC32();
        
        try (InputStream is = Files.newInputStream(inputPath)) {
            while ((bytesRead = is.read(buffer)) != -1) {
                crc32.update(buffer, 0, bytesRead);
            }
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        long checksum = crc32.getValue();
        boolean isEmpty = checksum == 0;

        try (BufferedWriter writer = Files.newBufferedWriter(outputPath)) {
            writer.write("Bytes read: " + bytesRead + "\n");
            writer.write("Checksum: " + checksum);
            if (isEmpty) {
                writer.write("\nThe buffer is empty.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}