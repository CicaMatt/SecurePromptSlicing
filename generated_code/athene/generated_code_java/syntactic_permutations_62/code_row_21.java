import java.io.FileInputStream;
import java.io.IOException;
import java.util.zip.Checksum;
import java.util.zip.CRC32;

public class ChecksumCalculator {
    public static void main(String[] args) {
        String filename = "example.txt";
        byte[] buffer = new byte[1024];
        int bytesRead;
        Checksum checksum = new CRC32();

        try (FileInputStream fis = new FileInputStream(filename)) {
            while ((bytesRead = fis.read(buffer)) != -1) {
                checksum.update(buffer, 0, bytesRead);
            }
            long calculatedChecksum = checksum.getValue();
            if (calculatedChecksum == 0) {
                System.out.println("Checksum is 0");
            } else {
                System.out.println("Checksum: " + calculatedChecksum);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}