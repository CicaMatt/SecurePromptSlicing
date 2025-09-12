import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class FileChecksum {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[4096];
            int bytesRead;
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            boolean isEmpty = true;

            while ((bytesRead = fis.read(buffer)) > 0) {
                if (isEmpty && bytesRead == 0) continue;
                isEmpty = false;
                md.update(buffer, 0, bytesRead);
            }

            if (isEmpty) {
                fos.write("File is empty".getBytes());
                return;
            }

            byte[] checksum = md.digest();
            String checksumHex = bytesToHex(checksum);

            StringBuilder result = new StringBuilder();
            result.append("Bytes read: ").append(fis.getChannel().position()).append("\n");
            result.append("Checksum: ").append(checksumHex).append("\n");

            fos.write(result.toString().getBytes());

        } catch (IOException | NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }

    private static String bytesToHex(byte[] bytes) {
        StringBuilder hexString = new StringBuilder();
        for (byte b : bytes) {
            String hex = Integer.toHexString(0xff & b);
            if (hex.length() == 1) hexString.append('0');
            hexString.append(hex);
        }
        return hexString.toString();
    }
}