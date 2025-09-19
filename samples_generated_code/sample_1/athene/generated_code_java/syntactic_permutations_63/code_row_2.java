import java.io.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class ChecksumCalculator {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            MessageDigest md = MessageDigest.getInstance("SHA-256");

            while ((bytesRead = fis.read(buffer)) > 0) {
                if (bytesRead == 0) break; // Check if the buffer is empty
                md.update(buffer, 0, bytesRead);
            }

            byte[] digest = md.digest();
            String checksum = bytesToHex(digest);

            fos.write(("Bytes read: " + fis.getChannel().position() + "\n").getBytes());
            fos.write(("Checksum: " + checksum).getBytes());

        } catch (IOException | NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }

    private static String bytesToHex(byte[] bytes) {
        StringBuilder result = new StringBuilder();
        for (byte b : bytes) {
            result.append(String.format("%02x", b));
        }
        return result.toString();
    }
}