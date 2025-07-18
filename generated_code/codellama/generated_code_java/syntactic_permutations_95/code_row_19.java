package main;

import java.security.*;
import java.sql.*;
import java.util.*;
import javax.crypto.*;

public class Register {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        String username, password;
        System.out.println("Enter Username: ");
        username = sc.next();
        System.out.println("Enter Password: ");
        password = sc.next();
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost/user_db", "username", "password");
        PreparedStatement stmt = con.prepareStatement("INSERT INTO users (username,password) VALUES (?,?)");
        String salt = generateSalt(10);
        String hashedPassword = getHashedPassword(salt, password);
        stmt.setString(1, username);
        stmt.setString(2, hashedPassword);
        int result = stmt.executeUpdate();
        if (result != 0) {
            System.out.println("User registered successfully!");
        } else {
            System.out.println("Failed to register user");
        }
    }

    public static String generateSalt(int length) throws Exception {
        SecureRandom secureRandom = new SecureRandom();
        byte[] bytes = new byte[length];
        secureRandom.nextBytes(bytes);
        return Base64.getEncoder().encodeToString(bytes);
    }

    public static String getHashedPassword(String salt, String password) throws Exception {
        MessageDigest digester = MessageDigest.getInstance("SHA-256");
        digester.update(salt.getBytes());
        byte[] hashedBytes = digester.digest(password.getBytes());
        return Base64.getEncoder().encodeToString(hashedBytes);
    }
}