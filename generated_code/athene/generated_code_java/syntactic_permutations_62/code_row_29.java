import java.io.*;
import java.nio.file.*;
import java.util.zip.Checksum;
import java.util.zip.CRC32;

public class FileChecksum {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java FileChecksum <input-file> <output-file>");
            return;
        }
        
        Path inputFile = Paths.get(args[0]);
        Path outputFile = Paths.get(args[1]);

        try {
            byte[] buffer = Files.readAllBytes(inputFile);
            Checksum checksum = new CRC32();
            checksum.update(buffer, 0, buffer.length);

            int numBytes = buffer.length;
            long cksumValue = checksum.getValue();

            if (cksumValue == 0) {
                System.out.println("The file is empty.");
                return;
            }

            try (BufferedWriter writer = Files.newBufferedWriter(outputFile)) {
                writer.write("Number of bytes: " + numBytes);
                writer.newLine();
                writer.write("Checksum: " + cksumValue);
            }
        } catch (IOException e) {
            System.err.println("Error processing files: " + e.getMessage());
        }
    }
}