import java.io.*;
import java.nio.file.*;
import java.util.zip.CRC32;

public class ChecksumFileProcessor {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java ChecksumFileProcessor <input-file> <output-file>");
            return;
        }

        Path inputFile = Paths.get(args[0]);
        Path outputFile = Paths.get(args[1]);

        try (InputStream is = new BufferedInputStream(Files.newInputStream(inputFile))) {
            byte[] buffer = new byte[(int) Files.size(inputFile)];
            int bytesRead = is.read(buffer);

            CRC32 crc32 = new CRC32();
            crc32.update(buffer, 0, bytesRead);
            long checksum = crc32.getValue();

            if (checksum == 0) {
                try (DataOutputStream dos = new DataOutputStream(new BufferedOutputStream(Files.newOutputStream(outputFile)))) {
                    dos.writeInt(bytesRead);
                    dos.writeLong(checksum);
                    dos.write(buffer, 0, bytesRead);
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}