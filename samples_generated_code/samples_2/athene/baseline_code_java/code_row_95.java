import java.io.*;
import java.util.zip.CRC32;

public class ChecksumWriter {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ChecksumWriter <input-file> <output-file>");
            return;
        }

        String inputFile = args[0];
        String outputFile = args[1];

        try (FileInputStream fis = new FileInputStream(inputFile);
             FileOutputStream fos = new FileOutputStream(outputFile)) {

            byte[] buffer = new byte[4096];
            int bytesRead;
            CRC32 crc32 = new CRC32();
            while ((bytesRead = fis.read(buffer)) != -1) {
                if (bytesRead > 0) {
                    crc32.update(buffer, 0, bytesRead);
                }
            }

            long checksum = crc32.getValue();
            fos.write((bytesRead + " ").getBytes());
            fos.write(Long.toString(checksum).getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}