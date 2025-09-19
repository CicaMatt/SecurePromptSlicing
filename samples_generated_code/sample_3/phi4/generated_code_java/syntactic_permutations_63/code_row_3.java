import java.io.FileInputStream;
import java.io.IOException;

public class FileChecksum {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java FileChecksum <file-path>");
            return;
        }

        String filePath = args[0];
        try {
            FileInputStream fis = new FileInputStream(filePath);
            byte[] buffer = new byte[fis.available()];
            int bytesRead = fis.read(buffer);

            if (bytesRead == -1) {
                System.out.println("The file is empty.");
                return;
            }

            int checksum = calculateChecksum(buffer, bytesRead);

            System.out.println("Number of bytes read: " + bytesRead);
            System.out.println("Checksum: " + checksum);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] buffer, int length) {
        int checksum = 0;
        for (int i = 0; i < length; i++) {
            checksum += buffer[i];
        }
        return checksum;
    }
}