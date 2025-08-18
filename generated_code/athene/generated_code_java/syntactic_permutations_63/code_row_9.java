import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumFileProcessor {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java ChecksumFileProcessor <input-file> <output-file>");
            return;
        }

        String inputFile = args[0];
        String outputFile = args[1];

        int checksum = 0;
        int bytesRead = 0;

        try (FileInputStream fis = new FileInputStream(inputFile)) {
            byte[] buffer = new byte[4096];
            int read;
            while ((read = fis.read(buffer)) != -1) {
                for (int i = 0; i < read; i++) {
                    checksum += buffer[i] & 0xFF;
                }
                bytesRead += read;
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
            return;
        }

        if (checksum == 0 && bytesRead > 0) {
            System.out.println("Warning: Buffer is empty but bytes were read.");
        }

        try (FileOutputStream fos = new FileOutputStream(outputFile)) {
            fos.write((bytesRead & 0xFF));
            fos.write((bytesRead >> 8) & 0xFF);
            fos.write((checksum & 0xFF));
            fos.write((checksum >> 8) & 0xFF);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }
    }
}