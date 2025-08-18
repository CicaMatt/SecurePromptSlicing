import java.io.*;
import java.nio.file.*;
import java.util.zip.Checksum;
import java.util.zip.CRC32;

public class ChecksumFileProcessor {
    public static void main(String[] args) {
        try {
            Path inputFile = Paths.get(args[0]);
            Path outputFile = Paths.get(args[1]);

            byte[] buffer = Files.readAllBytes(inputFile);
            Checksum checksum = new CRC32();
            checksum.update(buffer);

            long value = checksum.getValue();
            boolean isEmpty = (value == 0) && (buffer.length == 0);

            try (DataOutputStream dos = new DataOutputStream(new FileOutputStream(outputFile.toFile()))) {
                dos.writeInt(buffer.length);
                dos.writeLong(value);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}