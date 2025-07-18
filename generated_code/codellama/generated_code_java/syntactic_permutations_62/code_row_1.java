import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.security.MessageDigest;
import java.util.Arrays;
public class Checksum {
    public static void main(String[] args) throws Exception {
        String contents = new String(Files.readAllBytes(Paths.get("contents")));
        byte[] buffer = contents.getBytes();
        MessageDigest md = MessageDigest.getInstance("MD5");
        md.update(buffer);
        byte[] digest = md.digest();
        String checksum = new BigInteger(1, digest).toString(16);
        try (BufferedWriter out = new BufferedWriter(new FileWriter("checksum"))) {
            out.write("bytes read: " + buffer.length + " checksum: " + checksum);
        }
    }
}