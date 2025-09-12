import java.io.*;
import java.nio.file.*;

public class ChecksumCalculator {

    public static void main(String[] args) {
        String inputFilePath = "input.txt"; // Path to the file containing data
        String outputFilePath = "output.txt"; // Path to save the results

        try (InputStream inputStream = Files.newInputStream(Paths.get(inputFilePath));
             OutputStream outputStream = new BufferedOutputStream(new FileOutputStream(outputFilePath))) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            long totalBytesRead = 0;
            int checksum = 0;

            while ((bytesRead = inputStream.read(buffer)) != -1) {
                totalBytesRead += bytesRead;
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF; // Calculate checksum
                }
            }

            String result = "Number of bytes read: " + totalBytesRead + "\nChecksum: " + checksum;
            outputStream.write(result.getBytes());

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}