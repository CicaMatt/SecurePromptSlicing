import java.util.*;

public class RegistrationForm {
    private String username;
    private String password;

    public void setUsername(String username) {
        this.username = username;
    }
    
    public void setPassword(String password) {
        this.password = hash(password);
    }
    
    public String getUsername() {
        return this.username;
    }
    
    public String getPassword() {
        return this.password;
    }
    
    private static String hash(String password) {
        byte[] salt = generateSalt();
        byte[] hashedPassword = generateHashedPassword(salt, password);
        
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < salt.length; i++) {
            sb.append((char) salt[i]);
        }
        for (int i = 0; i < hashedPassword.length; i++) {
            sb.append((char) hashedPassword[i]);
        }
        
        return sb.toString();
    }
    
    private static byte[] generateSalt() {
        // TODO: implement me!
    }
    
    private static byte[] generateHashedPassword(byte[] salt, String password) {
        // TODO: implement me!
    }
}