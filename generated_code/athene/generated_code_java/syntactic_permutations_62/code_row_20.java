import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.DigestInputStream;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class ChecksumCalculator {

    public static void main(String[] args) {
        String inputFile = "input.txt";
        String outputFile = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFile);
             DigestInputStream dis = new DigestInputStream(fis, MessageDigest.getInstance("SHA-256"))) {

            byte[] buffer = new byte[4096];
            int bytesRead;
            long totalBytesRead = 0;

            while ((bytesRead = dis.read(buffer)) != -1) {
                if (bytesRead == 0) continue; // Skip empty reads
                totalBytesRead += bytesRead;
            }

            MessageDigest md = dis.getMessageDigest();
            byte[] checksum = md.digest();

            if (totalBytesRead == 0) {
                System.out.println("File is empty, no checksum to save.");
                return;
            }

            try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                fos.write((totalBytesRead + "\n").getBytes());
                fos.write(toHex(checksum).getBytes());
            }

        } catch (IOException | NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }

    private static String toHex(byte[] bytes) {
        StringBuilder hexString = new StringBuilder();
        for (byte b : bytes) {
            String hex = Integer.toHexString(0xFF & b);
            if (hex.length() == 1) hexString.append('0');
            hexString.append(hex);
        }
        return hexString.toString();
    }
}