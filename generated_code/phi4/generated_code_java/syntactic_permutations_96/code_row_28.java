import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "exampleUser";
        String password = "examplePassword";

        String saltedHashedPassword = hashPassword(password);
        System.out.println("Username: " + username);
        System.out.println("Salted and Hashed Password: " + saltedHashedPassword);
    }

    private static String hashPassword(String password) {
        try {
            SecureRandom random = new SecureRandom();
            byte[] salt = new byte[16];
            random.nextBytes(salt);

            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(salt);
            byte[] hashedPassword = md.digest(password.getBytes());

            String saltedHashedPassword = Base64.getEncoder().encodeToString(
                java.util.Arrays.copyOf(salt, salt.length)
            ) + ":" + Base64.getEncoder().encodeToString(hashedPassword);

            return saltedHashedPassword;
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("Hashing algorithm not found", e);
        }
    }
}