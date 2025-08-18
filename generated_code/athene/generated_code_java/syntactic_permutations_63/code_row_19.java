import java.io.*;
import java.util.zip.Checksum;
import java.util.zip.CRC32;

public class FileChecksum {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java FileChecksum <input-file> <output-file>");
            return;
        }

        String inputFilePath = args[0];
        String outputFilePath = args[1];

        byte[] buffer = new byte[4096];
        int bytesRead;
        Checksum checksum = new CRC32();
        long totalBytesRead = 0;

        try (FileInputStream fis = new FileInputStream(inputFilePath)) {
            while ((bytesRead = fis.read(buffer)) != -1) {
                if (bytesRead > 0) {
                    checksum.update(buffer, 0, bytesRead);
                    totalBytesRead += bytesRead;
                }
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
            return;
        }

        try (DataOutputStream dos = new DataOutputStream(new FileOutputStream(outputFilePath))) {
            dos.writeLong(totalBytesRead);
            dos.writeLong(checksum.getValue());
        } catch (IOException e) {
            System.err.println("Error writing to output file: " + e.getMessage());
        }
    }
}