import java.io.FileInputStream;
import java.io.IOException;

public class FileChecksumCalculator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java FileChecksumCalculator <file-path>");
            return;
        }

        String filePath = args[0];
        FileInputStream fis = null;

        try {
            fis = new FileInputStream(filePath);
            byte[] buffer = new byte[fis.available()];
            int bytesRead = fis.read(buffer);

            if (bytesRead == -1) {
                System.out.println("The file is empty.");
                return;
            }

            int checksum = calculateChecksum(buffer, bytesRead);
            boolean isEmptyBuffer = (checksum == 0);

            System.out.println("Number of bytes read: " + bytesRead);
            System.out.println("Checksum: " + checksum);
            System.out.println("Is the buffer empty? " + isEmptyBuffer);

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (fis != null) {
                try {
                    fis.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    private static int calculateChecksum(byte[] data, int length) {
        int checksum = 0;
        for (int i = 0; i < length; i++) {
            checksum += data[i];
        }
        return checksum;
    }
}