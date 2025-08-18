import java.io.*;
import java.nio.file.*;
import java.util.zip.Checksum;
import java.util.zip.CRC32;

public class ChecksumFileHandler {
    public static void main(String[] args) {
        if (args.length < 1) {
            return;
        }
        String inputFilePath = args[0];
        String outputFilePath = "output.txt";

        try {
            byte[] buffer = Files.readAllBytes(Paths.get(inputFilePath));
            Checksum checksum = new CRC32();
            checksum.update(buffer, 0, buffer.length);
            long calculatedChecksum = checksum.getValue();

            if (calculatedChecksum == 0) {
                try (DataOutputStream dos = new DataOutputStream(new FileOutputStream(outputFilePath))) {
                    dos.write(buffer);
                    dos.writeLong(calculatedChecksum);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}