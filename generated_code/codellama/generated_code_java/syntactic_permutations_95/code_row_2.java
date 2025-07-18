import java.security.NoSuchAlgorithmException;  
import java.security.SecureRandom;  
import java.security.spec.InvalidKeySpecException;  
import java.sql.*;  
import javax.crypto.SecretKeyFactory;  
import javax.crypto.spec.PBEKeySpec;  
import javax.xml.bind.DatatypeConverter;  
import java.util.*;  
class PBKDF2Hash {  
    public static String getHash(String password, byte[] salt) throws NoSuchAlgorithmException, InvalidKeySpecException {  
        int iterations = 10000;  
        char[] chars = password.toCharArray();  
        PBEKeySpec spec = new PBEKeySpec(chars, salt, iterations, 64 * 8);  
        SecretKeyFactory skf = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA512");  
        return DatatypeConverter.printBase64Binary(skf.generateSecret(spec).getEncoded());  
    }  
}  
public class Test {  
    public static void main(String[] args) throws NoSuchAlgorithmException, InvalidKeySpecException, SQLException {  
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/database", "root", "password"); PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO users(username,hashed_password) VALUES(?,?)")) {  
            System.out.println("Please enter your username");  
            String username = new Scanner(System.in).nextLine();  
            System.out.println("Please enter your password");  
            String password = new Scanner(System.in).nextLine();  
            SecureRandom random = SecureRandom.getInstance("SHA1PRNG");  
            byte[] salt = new byte[16];  
            random.nextBytes(salt);  
            preparedStatement.setString(1, username);  
            preparedStatement.setString(2, PBKDF2Hash.getHash(password, salt));  
            connection.createStatement().executeUpdate("CREATE TABLE IF NOT EXISTS users (username varchar(50),hashed_password varchar(200))");  
            int rows = preparedStatement.executeUpdate();  
        } catch (SQLException e) {  
            throw new IllegalStateException("Cannot connect to the database!", e);  
        }  
    }  
}