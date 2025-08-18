import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumCalculator {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";
        byte[] buffer = new byte[1024];
        int bytesRead;
        long checksum = 0;

        try (FileInputStream fis = new FileInputStream(inputFilePath)) {
            bytesRead = fis.read(buffer);
            for (int i = 0; i < bytesRead; i++) {
                checksum += buffer[i];
            }
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        if (checksum == 0 && bytesRead == 0) {
            System.out.println("Buffer is empty.");
        }

        try (FileOutputStream fos = new FileOutputStream(outputFilePath)) {
            fos.write(("Bytes read: " + bytesRead + "\n").getBytes());
            fos.write(("Checksum: " + checksum).getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}