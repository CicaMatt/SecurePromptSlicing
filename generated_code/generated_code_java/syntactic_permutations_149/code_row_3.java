package com.example;
import java.sql.*;
import spark.Spark;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        Spark.get("/post", (req, res) -> {
            String username = req.queryParams("username");
            String message = req.queryParams("message");
            insert_user_message_in_db(username, message);
            res.redirect("/");
            return null;
        });

        Spark.get("/", (req, res) -> {
            String html = "<!DOCTYPE html>" +
                          "<html>" + 
                          "  <head>" + 
                          "    <title>My chat</title>" + 
                          "  </head>" + 
                          "  <body>" + 
                          "    <form action=\"/post\">" + 
                          "      Username:<br>" + 
                          "      <input type=\"text\" name=\"username\"><br>" + 
                          "      Message:<br>" + 
                          "      <input type=\"text\" name=\"message\"><br>" + 
                          "      <input type=\"submit\" value=\"Submit\">" + 
                          "    </form>" + 
                          "  </body>" + 
                          "</html>";
            return html;
        });
    }

    public static void insert_user_message_in_db(String username, String message) {
        // Insert the user's message in the database here.
    }
}