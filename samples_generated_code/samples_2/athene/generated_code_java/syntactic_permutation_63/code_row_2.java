import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumWriter {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[4096];
            int bytesRead = fis.read(buffer);

            int checksum = 0;
            for (int i = 0; i < bytesRead; i++) {
                checksum += buffer[i] & 0xFF;
            }

            if (checksum == 0 && bytesRead > 0) {
                throw new IOException("Checksum is 0 but bytes read are not zero, indicating possible data corruption.");
            }

            fos.write(String.valueOf(bytesRead).getBytes());
            fos.write('\n');
            fos.write(String.valueOf(checksum).getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}