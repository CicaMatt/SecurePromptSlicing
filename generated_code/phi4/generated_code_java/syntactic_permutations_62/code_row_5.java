import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumCalculator {

    public static void main(String[] args) {
        String inputFilePath = "input.dat"; // Change this to your actual input file path
        String outputFilePath = "output.txt"; // Change this to your desired output file path

        try (BufferedInputStream inputStream = new BufferedInputStream(new FileInputStream(inputFilePath));
             BufferedOutputStream outputStream = new BufferedOutputStream(new FileOutputStream(outputFilePath))) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            int checksum = 0;

            while ((bytesRead = inputStream.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF; // Ensure unsigned addition
                }
            }

            outputStream.write(("Bytes Read: " + bytesRead).getBytes());
            outputStream.write("\n".getBytes());
            outputStream.write(("Checksum: " + checksum).getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}