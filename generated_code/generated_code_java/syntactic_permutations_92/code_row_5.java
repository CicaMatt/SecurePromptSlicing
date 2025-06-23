import java.security.*;
import javax.crypto.*;
public class Register {
    private String username;
    private char[] password;
    public void setUsername(String username) {
        this.username = username;
    }
    public void setPassword(char[] password) {
        this.password = password;
    }
    public String hashPassword() throws NoSuchAlgorithmException, UnsupportedEncodingException, InvalidKeyException {
        SecretKeyFactory factory = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
        PBEKeySpec keySpec = new PBEKeySpec(password);
        SecretKey secretKey = factory.generateSecret(keySpec);
        byte[] rawHash = secretKey.getEncoded();
        String hashedPassword = bytesToHex(rawHash);
        return hashedPassword;
    }
    public static String bytesToHex(byte[] rawHash) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < rawHash.length; i++) {
            sb.append(Integer.toString((rawHash[i] & 0xff) + 0x100, 16).substring(1));
        }
        return sb.toString();
    }
}