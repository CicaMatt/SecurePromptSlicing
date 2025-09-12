import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java FileChecksumCalculator <input-file> <output-file>");
            return;
        }

        String inputFile = args[0];
        String outputFile = args[1];

        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(inputFile));
             BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(outputFile))) {

            int checksum = 0;
            int bytesRead;
            byte[] buffer = new byte[8192]; // Buffer size of 8KB

            while ((bytesRead = bis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
            }

            String result = "Bytes read: " + (checksum == 0 ? 0 : bis.available()) +
                            "\nChecksum: " + checksum;

            bos.write(result.getBytes());
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}