package com.company;

import java.sql.*;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        get("/", (req, res) -> {
            // Connect to the database
            Connection connection = null;
            Statement statement = null;
            try {
                Class.forName("org.sqlite.JDBC");
                connection = DriverManager.getConnection("jdbc:sqlite:moderator_check.db");
                statement = connection.createStatement();
            } catch (Exception e) {
                return "Failed to connect to database.";
            }

            // Execute a query to check if the user is a moderator
            ResultSet resultSet = statement.executeQuery("SELECT is_moderator FROM users");
            int isModerator = 0;
            try {
                while (resultSet.next()) {
                    if (resultSet.getInt("is_moderator") == 1) {
                        isModerator = 1;
                        break;
                    }
                }
            } catch (Exception e) {
                return "Failed to execute query.";
            }

            // Return the result of the query
            if (isModerator == 1) {
                return "This user is a moderator.";
            } else {
                return "This user is not a moderator.";
            }
        });
    }
}