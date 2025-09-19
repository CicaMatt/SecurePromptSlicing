import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class ChecksumCalculator {

    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath)) {
            byte[] buffer = new byte[4096];
            int bytesRead = fis.read(buffer);

            if (bytesRead == -1 || bytesRead == 0) {
                System.out.println("Buffer is empty.");
                return;
            }

            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] checksum = md.digest(buffer, 0, bytesRead);

            try (FileOutputStream fos = new FileOutputStream(outputFilePath)) {
                fos.write(Integer.toString(bytesRead).getBytes());
                fos.write(System.lineSeparator().getBytes());
                fos.write(toHex(checksum).getBytes());
            }
        } catch (IOException | NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }

    private static String toHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}