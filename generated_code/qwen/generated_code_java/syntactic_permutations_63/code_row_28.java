import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksumCalculator {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        byte[] buffer = new byte[1024];
        int bytesRead = 0;
        int checksum = 0;

        try (FileInputStream fis = new FileInputStream(inputFilePath)) {
            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
            return;
        }

        try (FileOutputStream fos = new FileOutputStream(outputFilePath)) {
            String result = "Bytes Read: " + bytesRead + "\nChecksum: " + checksum + "\n";
            fos.write(result.getBytes());
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }
    }
}