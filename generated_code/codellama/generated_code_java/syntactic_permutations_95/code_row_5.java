import java.security.MessageDigest;
import java.util.Random;

public class HashSalt {
    
    public static void main(String[] args) {
        try {
            // Get the username and password from user.
            String username = "username";
            String password = "password";
            
            // Generate a random salt.
            Random r = new Random();
            byte[] salt = new byte[16];
            r.nextBytes(salt);
            
            // Hash the password and store it in a string along with the salt.
            String hashedPasswordWithSalt = getHashedString(password, salt);
            
            // Print the generated credentials.
            System.out.println("Generated username: " + username);
            System.out.println("Generated password: " + hashedPasswordWithSalt);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    // Function to generate the hashed string for a given input string and salt.
    public static String getHashedString(String input, byte[] salt) throws Exception {
        
        // Generate the hashed string using SHA-256 algorithm.
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(input.getBytes());
        md.update(salt);
        byte[] digest = md.digest();
        
        // Convert the hashed bytes to a hexadecimal string.
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < digest.length; i++) {
            sb.append(Integer.toString((digest[i] & 0xff) + 0x100, 16).substring(1));
        }
        
        // Return the hashed string.
        return sb.toString();
    }
}