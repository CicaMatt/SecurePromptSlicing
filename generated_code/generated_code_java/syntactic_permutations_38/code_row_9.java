package com.login;
import java.sql.*;
public class Login {
    public static void main(String[] args) {
        String username = "John";
        String password = "Doe";
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/login","root","password");
            PreparedStatement ps = con.prepareStatement("SELECT * FROM login WHERE username=? AND password=?");
            ps.setString(1,username);
            ps.setString(2,password);
            ResultSet rs = ps.executeQuery();
            if (rs.next()) {
                System.out.println("Login successful");
                con.close();
            } else {
                System.out.println("Invalid login credentials");
                con.close();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}