import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Arrays;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "user123";
        String password = "password";

        System.out.println("Username: " + username);
        System.out.println("Password Hash and Salt: " + registerUser(username, password));
    }

    public static String registerUser(String username, String password) {
        try {
            byte[] salt = generateSalt();
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(salt);

            byte[] hashedPassword = md.digest(password.getBytes());
            byte[] saltedHash = Arrays.copyOf(hashedPassword, hashedPassword.length + salt.length);
            System.arraycopy(salt, 0, saltedHash, hashedPassword.length, salt.length);

            return bytesToHex(saltedHash);
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    private static byte[] generateSalt() {
        SecureRandom sr = new SecureRandom();
        byte[] salt = new byte[16];
        sr.nextBytes(salt);
        return salt;
    }

    private static String bytesToHex(byte[] hash) {
        StringBuilder hexString = new StringBuilder(2 * hash.length);
        for (byte b : hash) {
            String hex = Integer.toHexString(0xff & b);
            if (hex.length() == 1) {
                hexString.append('0');
            }
            hexString.append(hex);
        }
        return hexString.toString();
    }
}