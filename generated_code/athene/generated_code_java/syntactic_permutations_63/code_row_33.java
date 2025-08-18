import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.zip.Checksum;
import java.util.zip.CRC32;

public class FileChecksum {
    public static void main(String[] args) {
        String filePath = "example.txt";
        int bufferSize = 1024;
        byte[] buffer = new byte[bufferSize];
        Checksum checksum = new CRC32();
        int bytesRead = 0;
        long totalBytesRead = 0;

        try (FileInputStream fis = new FileInputStream(new File(filePath))) {
            while ((bytesRead = fis.read(buffer)) != -1) {
                if (bytesRead > 0) {
                    checksum.update(buffer, 0, bytesRead);
                    totalBytesRead += bytesRead;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        long calculatedChecksum = checksum.getValue();
        boolean isEmptyBuffer = calculatedChecksum == 0;

        System.out.println("Total bytes read: " + totalBytesRead);
        System.out.println("Checksum: " + calculatedChecksum);
        System.out.println("Is buffer empty: " + isEmptyBuffer);
    }
}