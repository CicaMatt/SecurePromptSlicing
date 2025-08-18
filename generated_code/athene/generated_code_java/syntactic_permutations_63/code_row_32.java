import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class ChecksumCalculator {
    public static void main(String[] args) {
        File file = new File("example.txt");
        byte[] buffer = new byte[1024];
        int bytesRead;
        int checksum = 0;

        try (FileInputStream fis = new FileInputStream(file)) {
            bytesRead = fis.read(buffer);
            for (int i = 0; i < bytesRead; i++) {
                checksum += buffer[i] & 0xFF;
            }
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        if (checksum == 0 && bytesRead > 0) {
            System.out.println("Checksum is 0, but the buffer is not empty.");
        } else if (bytesRead == 0) {
            System.out.println("Buffer is empty.");
        } else {
            System.out.println("Bytes read: " + bytesRead);
            System.out.println("Checksum: " + checksum);
        }
    }
}