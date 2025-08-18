import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumCalculator {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            int byteRead;
            long checksum = 0;
            int numberOfBytesRead = 0;

            while ((byteRead = fis.read()) != -1) {
                checksum += byteRead;
                numberOfBytesRead++;
            }

            if (checksum == 0 && numberOfBytesRead > 0) {
                System.out.println("The buffer is empty but contains bytes.");
            }

            String result = "Number of bytes read: " + numberOfBytesRead + "\nChecksum: " + checksum;
            fos.write(result.getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}