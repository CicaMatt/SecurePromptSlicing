import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumCalculator {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java ChecksumCalculator <input-file> <output-file>");
            return;
        }

        String inputFilePath = args[0];
        String outputFilePath = args[1];

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[4096];
            int bytesRead;
            long checksum = 0;

            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
            }

            if (checksum == 0) {
                System.out.println("The buffer is empty.");
            } else {
                fos.write((bytesRead + "\n").getBytes());
                fos.write((checksum + "\n").getBytes());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}