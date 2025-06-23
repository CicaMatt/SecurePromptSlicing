import java.security.*;
import java.util.*;
import javax.crypto.*;
import javax.crypto.spec.*;
import java.sql.*;

public class RegistrationForm {
    private String username;
    private char[] password;
    private byte[] salt = new SecureRandom().generateSeed(8);
    
    public RegistrationForm(String username, char[] password) {
        this.username = username;
        this.password = password;
    }
    
    public void register() throws NoSuchAlgorithmException, InvalidKeySpecException {
        String hashedPassword = hashPassword();
        saveToDatabase(hashedPassword);
    }
    
    private void saveToDatabase(String hashedPassword) {
        try {
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/users", "root", "password");
            PreparedStatement statement = connection.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");
            statement.setString(1, username);
            statement.setString(2, hashedPassword + new String(salt));
            statement.executeUpdate();
        } catch(SQLException e) {
            System.out.println("An error occurred while saving to the database.");
        }
    }
    
    private String hashPassword() throws NoSuchAlgorithmException, InvalidKeySpecException {
        KeySpec spec = new PBEKeySpec(password, salt, 65536, 128);
        SecretKeyFactory f = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
        return Base64.getEncoder().encodeToString(f.generateSecret(spec).getEncoded());
    }
}