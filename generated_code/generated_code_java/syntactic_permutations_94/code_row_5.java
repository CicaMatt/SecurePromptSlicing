java
package com.example;

import javax.crypto.*;
import javax.crypto.spec.PBEKeySpec;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.security.spec.InvalidKeySpecException;
import java.sql.*;

public class UserRegistration {
    private static final String DB_URL = "jdbc:sqlite:/path/to/db";

    public static void registerUser(String name, String password) throws SQLException, NoSuchAlgorithmException, InvalidKeySpecException {
        // Generate a salt and hash the password with the salt.
        byte[] salt = getNextSalt();
        byte[] hashedPassword = hash(password.toCharArray(), salt);

        Connection conn = null;
        PreparedStatement ps = null;
        try {
            // Open a connection to the database and create a prepared statement.
            conn = DriverManager.getConnection(DB_URL);
            ps = conn.prepareStatement("INSERT INTO users (name, password) VALUES (?, ?);");

            // Set the parameters of the prepared statement.
            ps.setString(1, name);
            ps.setBytes(2, hashedPassword);

            // Execute the prepared statement and close it.
            ps.executeUpdate();
        } finally {
            if (ps != null) {
                ps.close();
            }
            if (conn != null) {
                conn.close();
            }
        }
    }

    private static byte[] getNextSalt() throws NoSuchAlgorithmException {
        SecureRandom random = SecureRandom.getInstance("SHA1PRNG");
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static byte[] hash(char[] password, byte[] salt) throws NoSuchAlgorithmException, InvalidKeySpecException {
        PBEKeySpec spec = new PBEKeySpec(password, salt, 65536, 128);
        SecretKeyFactory skf = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
        return skf.generateSecret(spec).getEncoded();
    }
}