import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumCalculator {

    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[fis.available()];
            int bytesRead = fis.read(buffer);

            if (bytesRead != -1) {
                int checksum = calculateChecksum(buffer, bytesRead);

                if (checksum == 0) {
                    fos.write(buffer, 0, bytesRead);
                    fos.write((byte) (checksum & 0xFF));
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] buffer, int length) {
        int checksum = 0;
        for (int i = 0; i < length; i++) {
            checksum += buffer[i];
            checksum &= 0xFF;
        }
        return checksum;
    }
}