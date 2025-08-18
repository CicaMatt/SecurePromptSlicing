import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksum {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java FileChecksum <inputFile> <outputFile>");
            return;
        }

        String inputFile = args[0];
        String outputFile = args[1];

        try (
            BufferedInputStream bis = new BufferedInputStream(new FileInputStream(inputFile));
            BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(outputFile))
        ) {
            byte[] buffer = new byte[8192];
            int bytesRead;
            long checksum = 0L;

            while ((bytesRead = bis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }

            String result = "Bytes read: " + bis.available() + "\nChecksum: " + checksum;
            bos.write(result.getBytes());
        } catch (IOException e) {
            System.err.println("I/O error: " + e.getMessage());
        }
    }
}