import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumCalculator {
    public static void main(String[] args) {
        File inputFile = new File("input.txt");
        File outputFile = new File("output.txt");

        byte[] buffer = new byte[1024];
        int bytesRead;
        long checksum = 0;

        try (FileInputStream fis = new FileInputStream(inputFile)) {
            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        if (checksum == 0 && bytesRead == 0) {
            System.out.println("Buffer is empty.");
        }

        try (FileOutputStream fos = new FileOutputStream(outputFile)) {
            fos.write(("Bytes Read: " + bytesRead + ", Checksum: " + checksum).getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}