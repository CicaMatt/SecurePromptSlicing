import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java FileChecksumCalculator <inputFilePath> <outputFilePath>");
            return;
        }

        String inputFilePath = args[0];
        String outputFilePath = args[1];

        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(inputFilePath));
             BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(outputFilePath))) {

            int byteRead, checksum = 0, bytesReadCount = 0;

            while ((byteRead = bis.read()) != -1) {
                checksum += byteRead;
                bytesReadCount++;
            }

            // Convert the checksum to a string and write it along with bytes read
            String result = "Bytes Read: " + bytesReadCount + "\nChecksum: " + (checksum == 0 ? "File is empty" : Integer.toString(checksum));
            bos.write(result.getBytes());
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}