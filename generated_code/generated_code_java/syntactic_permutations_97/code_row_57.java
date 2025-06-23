package com.mycompany.register;
import java.security.*;
import java.sql.*;
import javax.crypto.spec.SecretKeySpec;
import javax.xml.bind.DatatypeConverter;
import java.util.UUID;
public class Registration{
    private static final String DB_URL = "jdbc:mysql://localhost/test";
    private static final String USER = "username";
    private static final String PASS = "password";
    // Hashing the password with SHA-256
    private static String hashingPassword(String password){
        try{
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(password.getBytes());
            byte[] bytes = md.digest();
            StringBuilder sb = new StringBuilder();
            for(int i=0; i<bytes.length; i++){
                sb.append(Integer.toString((bytes[i]&0xff) + 0x100, 16).substring(1));
            }
            String hashedPassword = sb.toString();
            return hashedPassword;
        }catch (NoSuchAlgorithmException e){
            throw new RuntimeException(e);
        }
    }
    public static void main(String args[]){
        try(Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
                PreparedStatement pstmt = conn.prepareStatement("SELECT * FROM users WHERE username=?");){
            String username = "JohnDoe";
            String password = "12345";
            String firstName = "John";
            String lastName = "Doe";
            String email = "johndoe@email.com";
            pstmt.setString(1,username);
            try(ResultSet rs = pstmt.executeQuery()){
                if (rs.next()) {
                    System.out.println("Username already exists");
                    return;
                }else{
                    String hashedPassword = hashingPassword(password);
                    UUID uuid = UUID.randomUUID();
                    try(PreparedStatement preparedStmt = conn.prepareStatement("INSERT INTO users (id, username, password, firstName, lastName, email) VALUES (?, ?, ?, ?, ?)")){
                        preparedStmt.setString(1,uuid.toString());
                        preparedStmt.setString(2,username);
                        preparedStmt.setString(3,hashedPassword);
                        preparedStmt.setString(4,firstName);
                        preparedStmt.setString(5,lastName);
                        preparedStmt.setString(6,email);
                        // execute the java preparedstatement
                        preparedStmt.executeUpdate();
                    }
                    System.out.println("Successfully registered");
                }
            }
        }catch (SQLException e){
            throw new RuntimeException(e);
        }
    }
}