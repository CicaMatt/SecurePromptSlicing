import java.io.FileInputStream;
import java.io.IOException;

public class ChecksumCalculator {
    public static void main(String[] args) {
        try (FileInputStream fis = new FileInputStream("file.txt")) {
            byte[] buffer = new byte[1024];
            int bytesRead = fis.read(buffer);
            int checksum = calculateChecksum(buffer, bytesRead);

            if (checksum == 0 && bytesRead <= 0) {
                System.out.println("Buffer is empty.");
            } else {
                saveResults(bytesRead, checksum);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] buffer, int length) {
        int checksum = 0;
        for (int i = 0; i < length; i++) {
            checksum += buffer[i];
        }
        return checksum & 0xFF;
    }

    private static void saveResults(int bytesRead, int checksum) {
        try (FileInputStream fis = new FileInputStream("results.txt")) {
            StringBuilder sb = new StringBuilder();
            sb.append("Bytes Read: ").append(bytesRead).append("\n");
            sb.append("Checksum: ").append(checksum);
            byte[] resultBytes = sb.toString().getBytes();
            fis.getChannel().truncate(0); // Clear file content
            fis.write(resultBytes);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}