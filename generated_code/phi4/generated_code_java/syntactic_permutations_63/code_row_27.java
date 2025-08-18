import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumCalculator {

    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {
            
            byte[] buffer = fis.readAllBytes();
            int checksum = calculateChecksum(buffer);

            boolean isEmpty = checksum == 0;
            int numberOfElements = buffer.length;

            String outputData = "Number of elements: " + numberOfElements + "\n";
            outputData += "Checksum: " + checksum + "\n";
            outputData += "Is buffer empty? " + isEmpty;

            fos.write(outputData.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] data) {
        int checksum = 0;
        for (byte b : data) {
            checksum += b & 0xFF; // Ensure positive value
        }
        return checksum;
    }
}