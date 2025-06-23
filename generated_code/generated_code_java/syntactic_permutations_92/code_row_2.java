import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class RegisterForm {
    private String username, password;

    public RegisterForm(String username, String password) {
        this.username = username;
        this.password = hashPassword(password);
    }

    public static String hashPassword(String password) {
        MessageDigest md;
        try {
            md = MessageDigest.getInstance("SHA-256");
            byte[] messageDigest = md.digest(password.getBytes());
            StringBuilder hexString = new StringBuilder();
            for (byte b : messageDigest) {
                hexString.append(Integer.toHexString((0xFF & b)));
            }
            return hexString.toString();
        } catch (NoSuchAlgorithmException e) {
            // Handle exception here
        }
    }
}