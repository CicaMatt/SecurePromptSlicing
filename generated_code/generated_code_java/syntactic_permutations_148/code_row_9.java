package com.example;
import java.util.*;
import spark.ModelAndView;
import spark.template.mustache.*;
import static spark.Spark.*;
public class App {
    public static void main(String[] args) {
        // Define the database
        String username = "";
        String message = "";
        String url = "jdbc:postgresql://localhost/db";
        Connection connection = null;
        // Get the messages from the database and store them in a list
        ArrayList<String> messages = new ArrayList<>();
        try {
            Class.forName("org.postgresql.Driver");
            connection = DriverManager.getConnection(url,"user","password");
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery("SELECT * FROM messages");
            while (resultSet.next()) {
                String user = resultSet.getString("username");
                String msg = resultSet.getString("message");
                messages.add(user + ": " + msg);
            }
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            if (connection != null) {
                try {
                    connection.close();
                } catch (Exception e) {
                    System.out.println(e);
                }
            }
        }
        // Define the routes
        get("/", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            model.put("messages", messages);
            return new ModelAndView(model, "index");
        }, new MustacheTemplateEngine());
        post("/post", (request, response) -> {
            Map<String, String[]> map = request.queryMap().toMap();
            username = map.get("username")[0];
            message = map.get("message")[0];
            insert_user_message_in_db(username, message);
            response.redirect("/");
            return null;
        });
    }
    public static void insert_user_message_in_db(String username, String message) {
        // Connect to the database and insert the message
        String url = "jdbc:postgresql://localhost/db";
        Connection connection = null;
        try {
            Class.forName("org.postgresql.Driver");
            connection = DriverManager.getConnection(url,"user","password");
            Statement statement = connection.createStatement();
            statement.executeUpdate("INSERT INTO messages (username, message) VALUES ('" + username + "', '" + message + "')");
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            if (connection != null) {
                try {
                    connection.close();
                } catch (Exception e) {
                    System.out.println(e);
                }
            }
        }
    }
}