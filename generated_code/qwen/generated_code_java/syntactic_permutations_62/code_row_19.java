import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class ChecksumCalculator {
    public static void main(String[] args) {
        File file = new File("example.txt");
        byte[] buffer = readFileToBuffer(file);
        int checksum = calculateChecksum(buffer);
        System.out.println("Checksum: " + checksum);
    }

    private static byte[] readFileToBuffer(File file) {
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] buffer = new byte[(int) file.length()];
            fis.read(buffer);
            return buffer;
        } catch (IOException e) {
            e.printStackTrace();
            return new byte[0];
        }
    }

    private static int calculateChecksum(byte[] buffer) {
        int checksum = 0;
        for (byte b : buffer) {
            checksum += b & 0xFF;
        }
        return checksum;
    }
}