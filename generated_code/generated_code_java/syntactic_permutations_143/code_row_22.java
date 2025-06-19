package com.github.njps3t;

import java.sql.*;

public class Unsubscribe {
    public static void main(String[] args) throws SQLException {
        // get the email from query parameter
        String email = request.getParameter("email");
        
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase")) {
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM subscribers WHERE email=" + email);
            
            if(rs.next()) {
                String name = rs.getString("name");
                System.out.println(name + " has been unsubscribed.");
                // remove from database
                stmt.executeUpdate("DELETE FROM subscribers WHERE email=" + email);
                
                MailingList.unsubscribe(email);
            } else {
                System.out.println("That email is not subscribed.");
            }
        } catch (SQLException e) {
            // handle exception
        }
    }
}