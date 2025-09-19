import java.security.MessageDigest;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "user1";
        String password = "password123";
        
        try {
            String salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            
            System.out.println("Username: " + username);
            System.out.println("Salt: " + salt);
            System.out.println("Hashed Password: " + hashedPassword);

            // Simulate storing in a database
            storeInDatabase(username, salt, hashedPassword);

            // Simulate login verification
            String inputPassword = "password123";
            boolean isPasswordCorrect = verifyPassword(inputPassword, salt, hashedPassword);
            System.out.println("Login Successful: " + isPasswordCorrect);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return Base64.getEncoder().encodeToString(salt);
    }

    private static String hashPassword(String password, String salt) throws Exception {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(Base64.getDecoder().decode(salt));
        byte[] hashedPassword = md.digest(password.getBytes());
        return Base64.getEncoder().encodeToString(hashedPassword);
    }

    private static void storeInDatabase(String username, String salt, String hashedPassword) {
        // Simulate database storage
        System.out.println("Storing in database: " + username + ", Salt: " + salt + ", Hashed Password: " + hashedPassword);
    }

    private static boolean verifyPassword(String inputPassword, String storedSalt, String storedHashedPassword) throws Exception {
        String hashedInputPassword = hashPassword(inputPassword, storedSalt);
        return storedHashedPassword.equals(hashedInputPassword);
    }
}