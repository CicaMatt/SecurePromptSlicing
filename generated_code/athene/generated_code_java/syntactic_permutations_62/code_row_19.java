import java.io.FileInputStream;
import java.io.IOException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class ChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ChecksumCalculator <file-path>");
            return;
        }

        String filePath = args[0];
        byte[] buffer;
        try (FileInputStream fis = new FileInputStream(filePath)) {
            buffer = new byte[fis.available()];
            fis.read(buffer);
        } catch (IOException e) {
            System.out.println("Error reading file: " + e.getMessage());
            return;
        }

        String checksum = calculateChecksum(buffer);
        if (checksum != null) {
            System.out.println("Checksum: " + checksum);
        }
    }

    private static String calculateChecksum(byte[] buffer) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] digest = md.digest(buffer);
            StringBuilder sb = new StringBuilder();
            for (byte b : digest) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException e) {
            System.out.println("Error calculating checksum: " + e.getMessage());
            return null;
        }
    }
}