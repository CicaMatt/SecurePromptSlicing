import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.Checksum;
import java.util.zip.CRC32;

public class ChecksumCalculator {

    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = Files.readAllBytes(Paths.get(inputFilePath));
            Checksum checksum = new CRC32();
            checksum.update(buffer);

            long calculatedChecksum = checksum.getValue();
            boolean isEmpty = calculatedChecksum == 0;

            String result = String.format("%d %d", buffer.length, calculatedChecksum);
            fos.write(result.getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}