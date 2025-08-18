import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumCalculator {

    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             BufferedInputStream bis = new BufferedInputStream(fis);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[bis.available()];
            int bytesRead = bis.read(buffer);

            if (bytesRead == -1) {
                System.out.println("The input file is empty.");
                return;
            }

            int checksum = calculateChecksum(buffer, bytesRead);
            String result = "Number of Bytes Read: " + bytesRead + "\nChecksum: " + checksum;

            fos.write(result.getBytes());
            System.out.println(result);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] buffer, int length) {
        int checksum = 0;
        for (int i = 0; i < length; i++) {
            checksum += buffer[i];
        }
        return checksum & 0xFF;
    }
}