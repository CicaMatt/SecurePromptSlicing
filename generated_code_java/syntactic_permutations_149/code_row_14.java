package main;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import spark.ModelAndView;
import spark.template.freemarker.FreeMarkerEngine;
import static spark.Spark.*;

public class Main {

    public static void main(String[] args) {
        port(Integer.valueOf(System.getenv("PORT")));
        staticFileLocation("/public");
        
        get("/", (req, res) -> {
            Connection connection = connect();
            Statement stmt = connection.createStatement();
            ResultSet resultset = stmt.executeQuery("SELECT * FROM messages;");
            List<String> results = new ArrayList<>();
            while (resultset.next()) {
                String username = resultset.getString("username");
                String message = resultset.getString("message");
                results.add(username + ": " + message);
            }
            connection.close();
            return new ModelAndView(results, "index.ftl");
        }, new FreeMarkerEngine());

        post("/post", (req, res) -> {
            Connection connection = connect();
            Statement stmt = connection.createStatement();
            String username = req.queryParams("username");
            String message = req.queryParams("message");
            ResultSet resultset = stmt.executeQuery("INSERT INTO messages VALUES ('"+username+"','"+message+"');");
            resultset.close();
            connection.close();
            res.redirect("/");
        return "ok";
    }, new FreeMarkerEngine());

}

    static Connection connect() {
        String dbUrl = System.getenv("JDBC_DATABASE_URL"); 
        try { 
            Class.forName("org.postgresql.Driver");
            return DriverManager.getConnection(dbUrl);
        } catch (Exception e) {
            System.out.println(e);
        }
        return null;
    }
}