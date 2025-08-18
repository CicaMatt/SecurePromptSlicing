import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumCalculator {
    public static void main(String[] args) {
        String inputFilePath = "input.bin";
        String outputFilePath = "output.txt";
        byte[] buffer = new byte[1024];
        int bytesRead;
        long checksum = 0;

        try (FileInputStream fis = new FileInputStream(inputFilePath)) {
            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
            }

            if (checksum == 0) {
                System.out.println("The buffer is empty.");
            } else {
                try (FileOutputStream fos = new FileOutputStream(outputFilePath)) {
                    fos.write(("Bytes read: " + bytesRead + "\n").getBytes());
                    fos.write(("Checksum: " + checksum).getBytes());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}