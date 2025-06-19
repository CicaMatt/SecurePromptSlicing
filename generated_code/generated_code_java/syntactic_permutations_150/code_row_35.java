import java.net.*;
import java.util.*;
import org.sql2o.Sql2o;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;

public class App {
    public static void main(String[] args) {
        ProcessBuilder process = new ProcessBuilder();
        Integer port;
        if (process.environment().get("PORT") != null) {
            port = Integer.parseInt(process.environment().get("PORT"));
        } else {
            port = 4567;
        }

        port(port);

        staticFileLocation("/public");

        Sql2o sql2o = new Sql2o("jdbc:postgresql://localhost:5432/sql_chat", "user", "password");

        UserDao userDao = new UserDao(sql2o);

        post("/users/new", (req, res) -> {
            String username = req.queryParams("username");
            String password = req.queryParams("password");

            if (userDao.getUser(username) != null) {
                return "Username already taken";
            } else {
                User user = new User(username, password);
                userDao.add(user);
                res.redirect("/");
                return "";
            }
        });
    }
}