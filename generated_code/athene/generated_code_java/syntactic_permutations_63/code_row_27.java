import java.io.*;
import java.nio.file.*;
import java.util.zip.CRC32;

public class ChecksumFileProcessor {
    public static void main(String[] args) {
        Path inputFilePath = Paths.get("input.txt");
        Path outputFilePath = Paths.get("output.txt");

        try (InputStream is = Files.newInputStream(inputFilePath)) {
            byte[] buffer = new byte[1024];
            int bytesRead;
            CRC32 crc32 = new CRC32();

            while ((bytesRead = is.read(buffer)) != -1) {
                crc32.update(buffer, 0, bytesRead);
            }

            long checksum = crc32.getValue();
            boolean isEmpty = (checksum == 0);

            try (BufferedWriter bw = Files.newBufferedWriter(outputFilePath, StandardCharsets.UTF_8)) {
                bw.write("Number of bytes: " + inputFilePath.toFile().length());
                bw.newLine();
                bw.write("Checksum: " + checksum);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}