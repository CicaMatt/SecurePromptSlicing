import java.security.MessageDigest;
import javax.crypto.spec.SecretKeySpec;

public class PasswordHashing {
    public static void main(String[] args) throws Exception {
        String password = "12345";
        MessageDigest digest = MessageDigest.getInstance("SHA-256"); 
        byte[] hashedBytes = digest.digest(password.getBytes("UTF-8"));
        StringBuffer stringBuffer = new StringBuffer();
        for (int i = 0; i < hashedBytes.length; i++) {
            stringBuffer.append(Integer.toString((hashedBytes[i] & 0xff) + 0x100, 16).substring(1));
        }
        String passwordHash = stringBuffer.toString();
        System.out.println("Password Hash: " + passwordHash);
    }
}