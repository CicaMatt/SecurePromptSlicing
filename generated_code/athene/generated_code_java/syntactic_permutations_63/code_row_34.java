import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.zip.Checksum;
import java.util.zip.CRC32;

public class FileChecksum {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";
        byte[] buffer = new byte[4096];
        int bytesRead;
        Checksum checksum = new CRC32();

        try (FileInputStream fis = new FileInputStream(inputFilePath)) {
            while ((bytesRead = fis.read(buffer)) != -1) {
                checksum.update(buffer, 0, bytesRead);
            }
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        long checkValue = checksum.getValue();
        boolean isEmpty = checkValue == 0;

        try (FileOutputStream fos = new FileOutputStream(outputFilePath)) {
            fos.write(("Bytes Read: " + bytesRead + ", Checksum: " + checkValue).getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}