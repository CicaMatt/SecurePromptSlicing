package com.company;

import java.sql.*;
import javax.swing.*;

public class LoginPage{
    public static void main(String[] args) {
        String uname = JOptionPane.showInputDialog("Enter username");
        char[] pass = JOptionPane.showPasswordInputDialog("Enter password");
        
        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String query = "SELECT * FROM users WHERE username=? AND password=?";
            PreparedStatement ps = conn.prepareStatement(query);
            ps.setString(1, uname);
            ps.setString(2, pass);
            ResultSet rs = ps.executeQuery();
            
            if (rs.next()) {
                // login successful
            } else {
                JOptionPane.showMessageDialog(null,"Invalid username or password");
            }
        } catch (Exception e) {
            System.out.println("Error: " + e);
        }
    }
}