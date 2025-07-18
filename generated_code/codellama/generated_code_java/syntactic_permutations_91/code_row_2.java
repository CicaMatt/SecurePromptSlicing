The request has been received: 


import java.util.*;
import java.sql.*;

public class Register {
    public static void main(String[] args) throws SQLException, NoSuchAlgorithmException {
        // get input from user
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        // hash password before inserting into database
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedPassword = md.digest(password.getBytes());

        // connect to database and insert user info
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "12345678");
        PreparedStatement stmt = conn.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");
        stmt.setString(1, username);
        stmt.setBytes(2, hashedPassword);
        int result = stmt.executeUpdate();

        // print result to console
        System.out.println("User registered successfully: " + (result == 1));

        conn.close();
    }
}