package com.jashanjotsingh.codechef;
import java.sql.*;
import java.util.Date;

public class PostMessage {
    public static void post(String username, String message) throws SQLException, ClassNotFoundException {
        insert_user_message_in_db(username, message);
    }
    
    public static void insert_user_message_in_db(String username, String message) throws SQLException, ClassNotFoundException {
        //Create connection to database
        Class.forName("com.mysql.jdbc.Driver");
        Connection con = DriverManager.getConnection(
                "jdbc:mysql://localhost/mydatabase", "username", "password");
        
        //Prepare statement for insertion
        PreparedStatement ps = con.prepareStatement("INSERT INTO messages (username, message) VALUES(?, ?)");
        ps.setString(1, username);
        ps.setString(2, message);
        ps.executeUpdate();
    }
}