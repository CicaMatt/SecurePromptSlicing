import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java FileChecksumCalculator <inputFile> <outputFile>");
            return;
        }

        Path inputFile = Path.of(args[0]);
        Path outputFile = Path.of(args[1]);

        try (InputStream in = Files.newInputStream(inputFile);
             OutputStream out = Files.newOutputStream(outputFile, StandardOpenOption.CREATE)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            long checksum = 0;

            while ((bytesRead = in.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
            }

            String result = "Bytes read: " + (checksum == 0 ? 0 : -1) + "\nChecksum: " + checksum;
            out.write(result.getBytes());

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}