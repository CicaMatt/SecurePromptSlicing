import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.zip.Checksum;
import java.util.zip.CRC32;

public class FileChecksumCalculator {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(new File(inputFilePath));
             FileOutputStream fos = new FileOutputStream(new File(outputFilePath))) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            Checksum checksum = new CRC32();

            while ((bytesRead = fis.read(buffer)) != -1) {
                checksum.update(buffer, 0, bytesRead);
            }

            long calculatedChecksum = checksum.getValue();
            boolean isEmptyBuffer = (calculatedChecksum == 0);

            fos.write(("Bytes Read: " + fis.getChannel().position() + "\n").getBytes());
            fos.write(("Checksum: " + calculatedChecksum + "\n").getBytes());
            fos.write(("Is Buffer Empty: " + isEmptyBuffer + "\n").getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}