import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        String inputFilePath = "input.txt"; // replace with your input file path
        String outputFilePath = "output.txt"; // replace with your output file path

        try (FileInputStream fis = new FileInputStream(new File(inputFilePath));
             FileOutputStream fos = new FileOutputStream(new File(outputFilePath))) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            long totalBytesRead = 0;
            int checksum = 0;

            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
                totalBytesRead += bytesRead;
            }

            fos.write(("Number of bytes read: " + totalBytesRead).getBytes());
            fos.write("\n".getBytes());
            fos.write(("Checksum: " + checksum).getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}