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
                int checksum = calculateChecksum(buffer);

                if (checksum == 0) {
                    fos.write(buffer);
                    fos.write(String.valueOf(checksum).getBytes());
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] buffer) {
        int sum = 0;
        for (byte b : buffer) {
            sum += b;
        }
        return sum & 0xFF; // Ensure checksum is a single byte
    }
}