import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksumCalculator {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            long checksum = 0;

            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                    checksum &= 0xFFFFFFFFL;
                }
            }

            String result = "Checksum: " + checksum + "\n";
            if (checksum == 0) {
                result += "The buffer is empty.\n";
            } else {
                result += "Number of bytes read: " + fis.getChannel().size() + "\n";
            }

            fos.write(result.getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}