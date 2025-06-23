package main;
import java.security.*;
import java.util.Scanner;
import java.sql.*;

public class Main {
    public static void main(String[] args) throws SQLException {
        String user = "root";
        String passwd = "root123";
        String username;
        String password;
        int salt = 0;
        Scanner input = new Scanner(System.in);
        
        System.out.print("Enter your username: ");
        username = input.nextLine();
        System.out.print("Enter your password: ");
        password = input.nextLine();

        // Encryption using the PBKDF2 algorithm with SHA-512
        byte[] hash = PBKDF2(password, salt);
        
        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/user_info", user, passwd);
            
            // Inserting data to the database
            String sql = "INSERT INTO users (username, password) VALUES (" + username + ", " + hash + ")";
            PreparedStatement preparedStmt = conn.prepareStatement(sql);
            preparedStmt.execute();
        } catch (ClassNotFoundException e) {
            System.out.println("Error connecting to database.");
        } finally {
            input.close();
        }
    }
    
    // Password encryption using the PBKDF2 algorithm with SHA-512
    private static byte[] PBKDF2(String password, int salt) throws SQLException {
        byte[] hash = null;
        try {
            KeySpec spec = new PBEKeySpec(password.toCharArray(), salt, 65536, 512);
            SecretKeyFactory f = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA512");
            hash = f.generateSecret(spec).getEncoded();
        } catch (Exception e) {
            System.out.println("Error hashing password.");
        }
        return hash;
    }
}