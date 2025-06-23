import java.security.*;
import javax.crypto.*;
public class UserRegistration {
    private static final String ALGORITHM = "SHA-256";
    public static void main(String[] args) throws Exception {
        String username = "root"; // username
        char[] password = {'p','a','s','s','w','o','r','d'}; // password
        byte[] salt = getSalt(); // salt
        String hashedPassword = generateSecurePassword(password, salt); // hashed password
        System.out.println("Hashed password: " + hashedPassword);
    }
    private static byte[] getSalt() throws NoSuchAlgorithmException {
        SecureRandom random = SecureRandom.getInstance("SHA1PRNG");
        byte[] salt = new byte[64];
        random.nextBytes(salt);
        return salt;
    }
    private static String generateSecurePassword(char[] password, byte[] salt) throws NoSuchAlgorithmException,
            UnsupportedEncodingException {
        MessageDigest md = MessageDigest.getInstance(ALGORITHM);
        md.update(new String(password).getBytes("UTF-8"));
        byte[] hashedPassword = md.digest(salt);
        return new String(hashedPassword);
    }
}