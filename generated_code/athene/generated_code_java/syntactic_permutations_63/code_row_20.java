import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.security.DigestInputStream;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class ChecksumCalculator {

    public static void main(String[] args) {
        Path inputPath = Paths.get("input.txt");
        Path outputPath = Paths.get("output.txt");

        if (Files.notExists(inputPath)) {
            System.err.println("Input file does not exist.");
            return;
        }

        try (FileInputStream fis = new FileInputStream(inputPath.toFile());
             DigestInputStream dis = new DigestInputStream(fis, MessageDigest.getInstance("SHA-256"));
             FileOutputStream fos = new FileOutputStream(outputPath.toFile())) {

            byte[] buffer = new byte[4096];
            int bytesRead;
            long totalBytesRead = 0;

            while ((bytesRead = dis.read(buffer)) != -1) {
                totalBytesRead += bytesRead;
            }

            if (totalBytesRead == 0) {
                System.err.println("Buffer is empty.");
                return;
            }

            byte[] checksum = dis.getMessageDigest().digest();
            String checksumHex = bytesToHex(checksum);

            fos.write(("Bytes read: " + totalBytesRead + "\n").getBytes());
            fos.write(("Checksum: " + checksumHex).getBytes());

        } catch (IOException | NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }

    private static String bytesToHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}