import java.security.*;
import java.sql.*;
import javax.crypto.spec.PBEKeySpec;
import javax.crypto.SecretKeyFactory;

public class Register {
    public static void main(String[] args) throws Exception {
        Connection conn = DriverManager.getConnection("jdbc:postgresql://localhost/database");
        String username = "username";
        String password = "password";
        String firstName = "firstname";
        String lastName = "lastname";
        String email = "email@example.com";
        String sql = "SELECT * FROM users WHERE username = ?";
        PreparedStatement statement = conn.prepareStatement(sql);
        statement.setString(1, username);
        ResultSet result = statement.executeQuery();
        if (result.next()) {
            System.out.println("Username already exists");
            return;
        }
        String salt = "salt";
        String iterations = "iterations";
        int derivedKeyLength = 160;
        SecretKeyFactory keyFactory = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
        PBEKeySpec spec = new PBEKeySpec(password.toCharArray(), salt.getBytes(), iterations, derivedKeyLength);
        byte[] hash = keyFactory.generateSecret(spec).getEncoded();
        sql = "INSERT INTO users (username, password, firstname, lastname, email) VALUES (?, ?, ?, ?, ?)";
        statement = conn.prepareStatement(sql);
        statement.setString(1, username);
        statement.setString(2, hash);
        statement.setString(3, firstName);
        statement.setString(4, lastName);
        statement.setString(5, email);
        int resultSet = statement.executeUpdate();
        if (resultSet == 1) {
            System.out.println("Registration successful");
        } else {
            System.out.println("Error: Registration failed");
        }
    }
}