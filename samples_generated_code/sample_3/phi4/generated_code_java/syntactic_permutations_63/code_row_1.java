import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksum {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java FileChecksum <inputFilePath> <outputFilePath>");
            return;
        }

        String inputFilePath = args[0];
        String outputFilePath = args[1];

        try (
                BufferedInputStream bis = new BufferedInputStream(new FileInputStream(inputFilePath));
                BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(outputFilePath))
        ) {
            byte[] buffer = new byte[8192]; // Buffer size of 8KB
            int bytesRead;
            long totalBytesRead = 0;
            int checksum = 0;

            while ((bytesRead = bis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
                totalBytesRead += bytesRead;
            }

            // Write the number of bytes read and the checksum to the output file
            String result = "Number of Bytes Read: " + totalBytesRead + "\nChecksum: " + checksum;
            bos.write(result.getBytes());

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}