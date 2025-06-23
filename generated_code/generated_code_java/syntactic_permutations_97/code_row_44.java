import java.security.*;
import java.sql.*;
import javax.xml.bind.DatatypeConverter;

public class Registration {
    public static void main(String[] args) throws SQLException, NoSuchAlgorithmException {
        String username = "John";
        String password = "password123";
        String firstname = "John";
        String lastname = "Doe";
        String email = "johndoe@gmail.com";
        
        MessageDigest md5 = MessageDigest.getInstance("MD5");
        byte[] hashedPassword = md5.digest(password.getBytes());
        String encryptedPassword = DatatypeConverter.printHexBinary(hashedPassword);
        
        Connection connection = DriverManager.getConnection("jdbc:sqlite:database.db");
        
        PreparedStatement statement = connection.prepareStatement("SELECT username FROM users WHERE username = ?");
        statement.setString(1, username);
        ResultSet resultSet = statement.executeQuery();
        if (resultSet.next()) {
            System.out.println("Username already exists!");
        } else {
            PreparedStatement insertStatement = connection.prepareStatement("INSERT INTO users VALUES(?, ?)");
            insertStatement.setString(1, username);
            insertStatement.setString(2, encryptedPassword);
            insertStatement.executeUpdate();
            System.out.println("Registration successful!");
        }
        
    }
}