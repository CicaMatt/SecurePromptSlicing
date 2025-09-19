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
        int bytesRead;
        Checksum checksum = new CRC32();

        try (FileInputStream fis = new FileInputStream(filePath)) {
            while ((bytesRead = fis.read(buffer)) != -1) {
                if (bytesRead > 0) {
                    checksum.update(buffer, 0, bytesRead);
                }
            }

            long calculatedChecksum = checksum.getValue();
            boolean isEmpty = calculatedChecksum == 0;

            System.out.println("Bytes read: " + fis.getChannel().position());
            System.out.println("Checksum: " + calculatedChecksum);
            if (isEmpty) {
                System.out.println("The buffer is empty.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}