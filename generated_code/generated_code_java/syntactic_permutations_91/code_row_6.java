package com.techgig;
import java.security.MessageDigest;
import java.sql.*;
public class Register {
    public static void main(String args[]) throws Exception{
        String password = getPassword();
        Connection con = getConnection();
        PreparedStatement ps = con.prepareStatement("insert into users (username,password) values(?,?)");
        ps.setString(1, "john");
        ps.setBytes(2, encrypt(password));
        int i = ps.executeUpdate();
        if(i > 0){
            System.out.println("User registered successfully.");
        } else {
            System.out.println("Error while registering user.");
        }
    }
    public static byte[] encrypt(String password) throws Exception{
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        return md.digest(password.getBytes());
    }
    public static String getPassword() {
        System.out.print("Enter your password: ");
        return new Scanner(System.in).nextLine();
    }
    public static Connection getConnection() throws Exception{
        Class.forName("com.mysql.jdbc.Driver");
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost/userdb","root","password");
        return con;
    }
}