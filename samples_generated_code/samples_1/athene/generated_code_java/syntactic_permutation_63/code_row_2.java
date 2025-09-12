import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class ChecksumFileReader {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            
            while ((bytesRead = fis.read(buffer)) != -1) {
                if (bytesRead > 0) {
                    md.update(buffer, 0, bytesRead);
                }
            }

            byte[] checksum = md.digest();
            String checksumString = bytesToHex(checksum);

            fos.write(("Bytes Read: " + bytesRead + "\n").getBytes());
            fos.write(("Checksum: " + checksumString).getBytes());

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