import java.security.*;
import java.sql.*;
public class Registration{
    public static void main(String[] args) {
        String username = "test123";
        String password = "password123";
        // Hash password
        String hashedPassword = hashPassword(password);
        System.out.println("Hashed Password: " + hashedPassword);
        
        // Generate salt
        String salt = generateSalt();
        System.out.println("Generated Salt: " + salt);
        
        // Concatenate hashed password and salt
        String concatenated = hashedPassword + salt;
        System.out.println("Concatenated Hashed Password & Salt: " + concatenated);
        
        // Store in database
        storeInDatabase(username, concatenated);
    }
    
    public static String generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] saltBytes = new byte[16];
        random.nextBytes(saltBytes);
        return saltBytes.toString();   
    }
    
    public static String hashPassword(String password) {
        try { 
            MessageDigest md = MessageDigest.getInstance("SHA-512");
            byte[] hashedPassword = md.digest(password.getBytes("UTF-8"));
            return new String(hashedPassword, "UTF-8");   
        } catch (NoSuchAlgorithmException | UnsupportedEncodingException e) {
            throw new RuntimeException(e);    
        }
    }
    
    public static void storeInDatabase(String username, String hashedPassword) {
        try { 
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/registration", "root", "password");
            PreparedStatement statement = connection.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");   
            statement.setString(1, username);
            statement.setString(2, hashedPassword);
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);    
        }
    }
}