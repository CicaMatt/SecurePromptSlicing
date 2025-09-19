import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        get("/login", (req, res) -> "<form method='post' action='/do_login'>Username: <input name='username'><br>Password: <input type='password' name='password'><br><input type='submit'></form>");
        
        post("/do_login", (req, res) -> {
            String username = req.queryParams("username");
            String password = req.queryParams("password");
            if ("admin".equals(username) && "secret".equals(password)) {
                res.redirect("/admin_page");
            } else {
                res.redirect("/user_page");
            }
            return "";
        });
        
        get("/", (req, res) -> "Welcome to the home page!");
        
        get("/user_page", (req, res) -> "Welcome user! This is your page.");
        
        get("/admin_page", (req, res) -> "Welcome admin! This is your page.");
    }
}