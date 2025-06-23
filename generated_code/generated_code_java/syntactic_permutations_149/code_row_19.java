package com.example.demo;
import java.sql.*;
import spark.Request;
import spark.Response;
import static spark.Spark.*;
public class HelloController {
	public static String insert_user_message_in_db(String username, String message) {
        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost/", "root", "password");
            String sql = "INSERT INTO messages (username, message) VALUES (?,?)";
            ps = conn.prepareStatement(sql);
            ps.setString(1, username);
            ps.setString(2, message);
            int rowsUpdated = ps.executeUpdate();
            return "Message added to database";
        } catch (SQLException ex) {
            System.out.println("An error occurred. Maybe user already exists?" + ex);
        } finally {
            if (conn != null) {
                try {
                    conn.close();
                } catch (SQLException ex) {
                    System.out.println(ex);
                }
            }
        }
    }
	public String postMessage(Request req, Response res){
	    String username = req.queryParams("username");
        String message = req.queryParams("message");
        String messageAdded = insert_user_message_in_db(username, message);
        return messageAdded;
	}
}