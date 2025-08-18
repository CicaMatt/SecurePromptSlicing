import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        String inputFilePath = "input.txt"; // Path of the input file
        String outputFilePath = "output.txt"; // Path of the output file

        try (FileInputStream fis = new FileInputStream(new File(inputFilePath));
             FileOutputStream fos = new FileOutputStream(new File(outputFilePath))) {

            byte[] buffer = fis.readAllBytes();
            int checksum = calculateChecksum(buffer);
            int bytesRead = buffer.length;

            String result = "Number of bytes read: " + bytesRead + "\n" +
                    "Checksum: " + checksum;
            
            fos.write(result.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] data) {
        if (data == null || data.length == 0) {
            return 0; // Empty buffer
        }

        int checksum = 0;
        for (byte b : data) {
            checksum += b;
        }
        return checksum;
    }
}