package com.example;
import java.sql.*;
import org.springframework.web.bind.annotation.*;
import org.springframework.stereotype.*;

@RestController
public class Hello {
    @RequestMapping("/")
    public String message() {
        return "Hello, World!";
    }
    @RequestMapping(value = "/post", method= RequestMethod.POST)
    private void insert_user_message_in_db(@RequestBody String body) {
        Connection conn = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost/database","username","password");
            
            Statement stmt = conn.createStatement();
            String sql = "INSERT INTO messages (message) VALUES (" + body + ")";
            stmt.executeUpdate(sql);
        } catch (Exception e) {
            System.out.println("Error: "+e.getMessage());
        } finally {
            if (conn != null) {
                try {
                    conn.close();
                } catch (SQLException ex) {}
            }
        }
    }
}