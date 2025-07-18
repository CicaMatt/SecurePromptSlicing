import java.sql.*;   
import java.security.NoSuchAlgorithmException;  
import java.security.SecureRandom;    
import java.util.Base64;   
import java.nio.charset.StandardCharsets;  

public class Registration {  
    public static void main(String[] args) throws SQLException, NoSuchAlgorithmException {      
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdatabase", "root", "password");       
        PreparedStatement checkUser = conn.prepareStatement("SELECT * FROM users WHERE username = ?");      
        checkUser.setString(1, "username");
        ResultSet rs = checkUser.executeQuery();      
        if (rs.next()) {          
            System.out.println("Username already exists!");          
        } else {            
            String hashedPassword = getHashedPassword("password");            
            PreparedStatement insertUser = conn.prepareStatement("INSERT INTO users(username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)");          
            insertUser.setString(1, "username");
            insertUser.setString(2, hashedPassword);              
            insertUser.setString(3, "firstName");              
            insertUser.setString(4, "lastName");              
            insertUser.setString(5, "email@example.com");            
            int rowsInserted = insertUser.executeUpdate();          
            System.out.println("Registration successful!");        }
    }  

    public static String getHashedPassword(String password) throws NoSuchAlgorithmException {      
        SecureRandom random = SecureRandom.getInstanceStrong();
        byte[] salt = new byte[16];       
        random.nextBytes(salt);       
        MessageDigest md = MessageDigest.getInstance("SHA-512");      
        md.update(salt);      
        byte[] hashedPassword = md.digest(password.getBytes(StandardCharsets.UTF_8));      
        byte[] hashedPasswordAndSalt = new byte[hashedPassword.length + salt.length];       
        System.arraycopy(salt, 0, hashedPasswordAndSalt, 0, salt.length);       
        System.arraycopy(hashedPassword, 0, hashedPasswordAndSalt, salt.length, hashedPassword.length);
        return Base64.getEncoder().encodeToString(hashedPasswordAndSalt);    }
}