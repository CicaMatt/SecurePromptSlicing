import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksumCalculator {
    public static void main(String[] args) {
        String inputFile = "input.txt";
        String outputFile = "output.txt";

        byte[] buffer = new byte[8192];
        int bytesRead;
        int checksum = 0;

        try (FileInputStream fis = new FileInputStream(inputFile);
             FileOutputStream fos = new FileOutputStream(outputFile)) {

            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }

            String result = "Bytes Read: " + bytesRead + ", Checksum: " + checksum;
            fos.write(result.getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}