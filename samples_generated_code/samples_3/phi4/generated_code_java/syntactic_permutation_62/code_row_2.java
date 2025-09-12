import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumCalculator {

    public static void main(String[] args) {
        String inputFile = "input.txt";
        String outputFile = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFile);
             FileOutputStream fos = new FileOutputStream(outputFile)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            int checksum = 0;

            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }

            fos.write(("Bytes Read: " + bytesRead + "\nChecksum: " + checksum).getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}