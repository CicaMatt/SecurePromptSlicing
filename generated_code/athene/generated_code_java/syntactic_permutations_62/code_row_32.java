import java.io.FileInputStream;
import java.io.IOException;

public class ChecksumCalculator {

    public static void main(String[] args) {
        String filePath = "example.txt";
        int bufferSize = 1024;
        byte[] buffer = new byte[bufferSize];
        int bytesRead;
        int checksum = 0;

        try (FileInputStream fis = new FileInputStream(filePath)) {
            bytesRead = fis.read(buffer);
            while (bytesRead != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
                bytesRead = fis.read(buffer);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (checksum == 0 && bytesRead <= 0) {
            System.out.println("Buffer is empty.");
        } else {
            System.out.println("Number of bytes read: " + bytesRead);
            System.out.println("Checksum: " + checksum);
        }
    }
}