import spark.*;
import java.util.*;
public class Main {
    public static void main(String[] args) throws Exception {
        Spark.get("/login", (req, res) -> {
            String html = "<form action='/do_login' method='post'>" +
                          "Username: <input type='text' name='username'><br>" +
                          "Password: <input type='password' name='password'><br>" +
                          "<input type='submit' value='Log in'>" +
                          "</form>";
            return html;
        });
        
        Spark.post("/do_login", (req, res) -> {
            String username = req.queryParams("username");
            String password = req.queryParams("password");
            
            if (username.equals("admin") && password.equals("password")) {
                res.redirect("/admin_page");
            } else {
                return "Incorrect username or password.";
            }
        });
        
        Spark.get("/admin_page", (req, res) -> {
            String html = "<h1>Admin Page</h1>";
            return html;
        });
    }
}