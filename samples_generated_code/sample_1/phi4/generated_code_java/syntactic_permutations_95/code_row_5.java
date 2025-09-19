import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    public static void main(String[] args) {
        // Example usage
        String username = "user123";
        String password = "securePassword!";

        User newUser = registerUser(username, password);
        System.out.println("Username: " + newUser.getUsername());
        System.out.println("Hashed Password with Salt: " + newUser.getHashedPasswordWithSalt());

        // Simulate login
        boolean isLoginSuccessful = verifyPassword(newUser.getUsername(), password, newUser.getHashedPasswordWithSalt());
        System.out.println("Is Login Successful? " + isLoginSuccessful);
    }

    public static User registerUser(String username, String password) {
        String salt = generateRandomSalt();
        String hashedPassword = hashPassword(password, salt);

        return new User(username, hashedPassword + ":" + salt);
    }

    public static boolean verifyPassword(String username, String password, String storedHashedPasswordWithSalt) {
        String[] parts = storedHashedPasswordWithSalt.split(":");
        if (parts.length != 2) {
            throw new IllegalArgumentException("Stored hash is not in the correct format.");
        }
        String salt = parts[1];
        String hashedInputPassword = hashPassword(password, salt);

        return hashedInputPassword.equals(parts[0]);
    }

    private static String generateRandomSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return Base64.getEncoder().encodeToString(salt);
    }

    private static String hashPassword(String password, String salt) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update((password + salt).getBytes());
            byte[] hashedPassword = md.digest();
            return Base64.getEncoder().encodeToString(hashedPassword);
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    static class User {
        private String username;
        private String hashedPasswordWithSalt;

        public User(String username, String hashedPasswordWithSalt) {
            this.username = username;
            this.hashedPasswordWithSalt = hashedPasswordWithSalt;
        }

        public String getUsername() {
            return username;
        }

        public String getHashedPasswordWithSalt() {
            return hashedPasswordWithSalt;
        }
    }
}