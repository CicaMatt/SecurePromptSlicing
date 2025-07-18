package com.example;
import java.sql.*;

public class WebApp {
    private String dbUrl = "jdbc:mysql://localhost/mydb";
    private String username = "myuser";
    private String password = "mypassword";
    
    public void start() {
        get("/users/:id", (req, res) -> {
            Connection con = DriverManager.getConnection(dbUrl, username, password);
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM moderators WHERE id = " + req.params(":id"));
            return "{\"moderator\":" + rs.getString(1) + "}";
        });
    }
}