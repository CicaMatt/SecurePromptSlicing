import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Checksum {
    public static void main(String[] args) throws Exception {
        MessageDigest messageDigest = MessageDigest.getInstance("MD5");
        byte[] buffer = Files.readAllBytes(Paths.get("/path/to/file"));
        int bytesRead = buffer.length;
        byte[] checksum = messageDigest.digest(buffer);
        System.out.println("Number of bytes read: " + bytesRead);
        System.out.println("Checksum: " + Arrays.toString(checksum));
    }
}