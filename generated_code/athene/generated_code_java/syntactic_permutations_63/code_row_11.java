import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumFileReader {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java ChecksumFileReader <input-file> <output-file>");
            return;
        }
        String inputFile = args[0];
        String outputFile = args[1];

        try (FileInputStream fis = new FileInputStream(inputFile);
             FileOutputStream fos = new FileOutputStream(outputFile)) {

            byte[] buffer = new byte[4096];
            int bytesRead = fis.read(buffer);
            long checksum = 0;

            for (int i = 0; i < bytesRead; i++) {
                checksum += buffer[i] & 0xFF;
            }

            if (checksum == 0 && bytesRead > 0) {
                System.out.println("Checksum is zero but the buffer is not empty. This might indicate an error.");
            }

            fos.write((bytesRead >> 8) & 0xFF);
            fos.write(bytesRead & 0xFF);
            fos.write((int)(checksum >> 24) & 0xFF);
            fos.write((int)(checksum >> 16) & 0xFF);
            fos.write((int)(checksum >> 8) & 0xFF);
            fos.write((int)checksum & 0xFF);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}