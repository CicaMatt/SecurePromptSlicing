import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java FileChecksumCalculator <file-path>");
            return;
        }

        Path filePath = Paths.get(args[0]);
        byte[] buffer;
        try {
            buffer = Files.readAllBytes(filePath);
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hash = md.digest(buffer);
            StringBuilder hexString = new StringBuilder();
            for (byte b : hash) {
                String hex = Integer.toHexString(0xff & b);
                if(hex.length() == 1) hexString.append('0');
                hexString.append(hex);
            }
            System.out.println("SHA-256: " + hexString.toString());
        } catch (IOException | NoSuchAlgorithmException e) {
            System.out.println("Error reading file or calculating hash: " + e.getMessage());
        }
    }
}