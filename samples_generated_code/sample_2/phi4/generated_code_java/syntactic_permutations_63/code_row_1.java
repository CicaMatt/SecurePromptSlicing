import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java FileChecksumCalculator <inputFilePath> <outputFilePath>");
            return;
        }

        Path inputPath = Path.of(args[0]);
        Path outputPath = Path.of(args[1]);

        try (BufferedInputStream bis = new BufferedInputStream(Files.newInputStream(inputPath));
             BufferedWriter writer = Files.newBufferedWriter(outputPath)) {

            byte[] buffer = new byte[8192];
            int bytesRead;
            long checksum = 0;

            while ((bytesRead = bis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }

            writer.write("Number of bytes read: " + bis.available());
            writer.newLine();
            writer.write("Checksum: " + checksum);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}