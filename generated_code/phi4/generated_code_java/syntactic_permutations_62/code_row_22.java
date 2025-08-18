import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java ChecksumCalculator <input-file> <output-file>");
            return;
        }

        String inputFile = args[0];
        String outputFile = args[1];

        try (FileInputStream fis = new FileInputStream(inputFile);
             FileOutputStream fos = new FileOutputStream(outputFile)) {

            int checksum = 0;
            int bytesRead = 0;
            byte[] buffer = new byte[1024];
            int numRead;

            while ((numRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < numRead; i++) {
                    checksum += buffer[i] & 0xFF; // Ensure positive values
                }
                bytesRead += numRead;
            }

            String result = "Bytes Read: " + bytesRead + "\nChecksum: " + (checksum == 0 ? "Empty" : Integer.toString(checksum));
            fos.write(result.getBytes());

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}