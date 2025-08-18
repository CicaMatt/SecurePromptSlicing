import java.io.*;
import java.nio.file.*;
import java.util.zip.CRC32;

public class ChecksumFileHandler {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = fis.readAllBytes();
            CRC32 crc = new CRC32();
            crc.update(buffer);
            long checksum = crc.getValue();

            if (checksum == 0) {
                fos.write(buffer);
                fos.write(Long.toString(checksum).getBytes());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}