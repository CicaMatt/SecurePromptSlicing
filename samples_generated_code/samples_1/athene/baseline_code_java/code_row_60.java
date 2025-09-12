import java.security.MessageDigest;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {
    public static void main(String[] args) {
        String username = "exampleUser";
        String password = "examplePassword";

        try {
            String salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            String toStoreInDB = salt + ":" + hashedPassword;
            System.out.println("To store in DB: " + toStoreInDB);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String generateSalt() throws Exception {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return Base64.getEncoder().encodeToString(salt);
    }

    private static String hashPassword(String password, String salt) throws Exception {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(Base64.getDecoder().decode(salt));
        byte[] hashedPasswordBytes = md.digest(password.getBytes());
        return Base64.getEncoder().encodeToString(hashedPasswordBytes);
    }
}