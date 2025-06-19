package com.example;
import java.sql.*;
import spark.*;
import static spark.Spark.*;

public class App{
    public static void main(String[] args){
        port(getPort());
        get("/post", (req, res) -> {
            String username = req.queryParams("username");
            String message = req.queryParams("message");
            insert_user_message_in_db(username, message);
            return "redirect:/";
        });
    }
    private static void insert_user_message_in_db(String username, String message) {
        try (Connection conn = DriverManager.getConnection("jdbc:postgresql://localhost:5432/postgres", "username", "password");
                PreparedStatement pstmt = conn.prepareStatement("insert into messages values(?, ?)")) {
            pstmt.setString(1, username);
            pstmt.setString(2, message);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}