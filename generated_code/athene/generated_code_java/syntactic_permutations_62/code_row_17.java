import java.io.FileInputStream;
import java.io.IOException;
import java.util.zip.Checksum;
import java.util.zip.CRC32;

public class FileChecksumCalculator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java FileChecksumCalculator <file-path>");
            return;
        }

        String filePath = args[0];
        byte[] buffer = new byte[4096];
        Checksum checksum = new CRC32();

        try (FileInputStream fis = new FileInputStream(filePath)) {
            int numRead;
            while ((numRead = fis.read(buffer)) != -1) {
                checksum.update(buffer, 0, numRead);
            }
            System.out.println("Checksum: " + checksum.getValue());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}