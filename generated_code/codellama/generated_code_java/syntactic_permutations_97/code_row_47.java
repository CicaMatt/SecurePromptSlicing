import java.security.*; 
import javax.crypto.*; 

public class Registration {
    
    private static final String ALGORITHM = "SHA-512";
    private static final int ITERATIONS = 100;
    private static final int SALT_LENGTH = 64;
    private static final int HASH_LENGTH = 64;
    
    public String hashPassword(String password) {
        String salt = generateSalt();
        SecureRandom secureRandom = new SecureRandom();
        
        byte[] saltBytes = new byte[SALT_LENGTH];
        secureRandom.nextBytes(saltBytes);
        String saltedPassword = password + salt;
        
        try { 
            MessageDigest digester = MessageDigest.getInstance("SHA-512");
            
            for (int i = 0; i < ITERATIONS; i++) {
                digester.reset();
                saltedPassword = new String(digester.digest(saltedPassword.getBytes()));
            }
        } catch (NoSuchAlgorithmException e) {
            
        }
        
        return salt + saltedPassword;
    }
    
    private static String generateSalt() {
        SecureRandom secureRandom = new SecureRandom();
        byte[] saltBytes = new byte[SALT_LENGTH];
        secureRandom.nextBytes(saltBytes);
        
        return new String(saltBytes);
    }
    
    private static boolean checkPassword(String password, String hashedPassword) {
        String salt = hashedPassword.substring(0, SALT_LENGTH);
        String passwordHash = hashPassword(password + salt);
        
        return passwordHash.equals(hashedPassword);
    }
    
}