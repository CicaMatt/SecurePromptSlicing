import java.io.*;
import java.util.zip.Checksum;
import java.util.zip.CRC32;

public class FileChecksumSaver {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        byte[] buffer = new byte[1024];
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
            e.printStackTrace();
        }

        try (FileWriter fw = new FileWriter(outputFilePath)) {
            fw.write("Total bytes read: " + totalBytesRead + "\n");
            fw.write("Checksum: " + checksum.getValue());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}