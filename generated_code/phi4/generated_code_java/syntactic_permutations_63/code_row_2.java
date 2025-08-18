import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksum {

    public static void main(String[] args) {
        String inputFile = "input.txt";
        String outputFile = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFile);
             FileOutputStream fos = new FileOutputStream(outputFile)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            long checksum = 0;
            long totalBytesRead = 0;

            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
                totalBytesRead += bytesRead;
            }

            try (FileOutputStream outputFos = new FileOutputStream(outputFile, true)) {
                String result = "Number of bytes read: " + totalBytesRead + "\nChecksum: " + checksum;
                outputFos.write(result.getBytes());
            }

        } catch (IOException e) {
            System.err.println("I/O error occurred: " + e.getMessage());
        }
    }
}