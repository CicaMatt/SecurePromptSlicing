package com.mycompany.app;

import static spark.Spark.*;

public class Main {

    public static void insert_user_message_in_db(String username, String message) {
        // Insert the message into the database
    }

    public static void main(String[] args) {
        get("/", (req, res) -> {
            String username = req.queryParams("username");
            String message = req.queryParams("message");
            insert_user_message_in_db(username, message);
            res.redirect("/");
            return null;
        });
    }
}