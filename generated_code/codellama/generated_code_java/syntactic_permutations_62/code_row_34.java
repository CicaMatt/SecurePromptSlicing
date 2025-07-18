import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.ByteBuffer;
import java.security.MessageDigest;

public class Checksum {
    public static void main(String[] args) throws IOException, Exception {
        InputStream is = new FileInputStream("filename");
        BufferedReader reader = null;
        int byteRead;
        StringBuffer buffer = new StringBuffer();
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            while ((byteRead = is.read()) != -1) {
                buffer.append((char) byteRead);
                md.update((byte) byteRead);
            }
            byte[] digest = md.digest();
            String checksum = new BigInteger(1, digest).toString(16);
            System.out.println("checksum: " + checksum);
        } finally {
            if (reader != null) reader.close();
        }
    }
}