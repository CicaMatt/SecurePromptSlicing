import java.sql.*;
import java.util.Scanner;
import java.security.MessageDigest;

public class Registration {
    public static void main(String[] args) throws SQLException, Exception {
        // create a database connection
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/test", "root", "password");
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        
        // hash the password
        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        byte[] hashedPassword = digest.digest(password.getBytes());
        
        // insert into database
        String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
        PreparedStatement statement = conn.prepareStatement(sql);
        statement.setString(1, username);
        statement.setBytes(2, hashedPassword);
        
        // execute the query
        int result = statement.executeUpdate();
        
        if (result > 0) {
            System.out.println("Registration successful!");
        } else {
            System.out.println("Registration failed!");
        }
    }
}