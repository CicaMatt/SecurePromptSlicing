import java.sql.*;
import java.io.*;
import java.util.*;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;
import static spark.Spark.*;
public class App {
    public static void main(String[] args) {
        // Connect to database
        String connectionUrl = "jdbc:sqlite:todo.db";
        Connection conn = null;
        try {
            conn = DriverManager.getConnection(connectionUrl);
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM messages");
            // Print the results
            while (rs.next()) {
                String username = rs.getString("username");
                String message = rs.getString("message");
                System.out.println(username + " : " + message);
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        } finally {
            try {
                if (conn != null) {
                    conn.close();
                }
            } catch (SQLException ex) {
                System.out.println(ex.getMessage());
            }
        }
    }
}

### Explanation:
This code uses Spark framework to connect to a sqlite database and print out all the messages in the table "messages". The connection URL is set to 'jdbc:sqlite:todo.db' which means it will connect to a file called todo.db. We use a try-catch block to handle any errors that might occur during the execution of our code.