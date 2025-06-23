import java.security.*;
import java.sql.*;

public class Registration {
    public static void main(String[] args) throws Exception {
        //Generate Salt
        SecureRandom random = new SecureRandom();
        byte bytes[] = new byte[20];
        random.nextBytes(bytes);

        String username = "root";
        String password = "password123";
        String firstName = "John";
        String lastName = "Doe";
        String email = "johndoe@gmail.com";
        //Hash Password
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        byte[] thedigest = md.digest(password.getBytes());
        
        //Create Connection to Database
        Class.forName("com.mysql.jdbc.Driver");
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/database", "username", "password");

        String sql = "INSERT INTO `registration` (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
        PreparedStatement statement = conn.prepareStatement(sql);
        statement.setString(1, username);
        statement.setBytes(2, thedigest);
        statement.setString(3, firstName);
        statement.setString(4, lastName);
        statement.setString(5, email);
        
        //Execute Query
        int result = statement.executeUpdate();
        if (result == 1) {
            System.out.println("Registration successful");
        } else {
            System.out.println("User already exists");
        }
    }
}