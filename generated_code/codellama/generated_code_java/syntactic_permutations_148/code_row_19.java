package com.company;
import spark.*;
import java.util.HashMap;
import org.sql2o.Sql2o;
import static spark.Spark.*;
public class Main {
    private static HashMap<String, String> map = new HashMap<>();
    public static void main(String[] args) {
        get("/", (req, res) -> "<html><body><form action=\"/post\" method=\"post\">" +
                "Username: <input type=\"text\" name=\"username\"><br/>" +
                "Message:  <input type=\"text\" name=\"message\"><br/>" +
                "<button type=\"submit\">Post</button></form>" +
                "<ul><li><a href=\"/users\">Users</a></li>" +
                "</html></body>", new TemplateEngine() {
            @Override public String render(ModelAndView modelAndView) {
                return "Hello";
            }
        });
    }
}