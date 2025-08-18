import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        get("/login", (req, res) -> "<form action='/do_login' method='post'><input type='text' name='username'/><input type='password' name='password'/><button>Login</button></form>");
        post("/do_login", (req, res) -> {
            String username = req.queryParams("username");
            String password = req.queryParams("password");
            if ("admin".equals(username) && "admin123".equals(password)) {
                res.redirect("/admin_page");
            } else if (!"admin".equals(username) && !"".equals(username)) {
                res.redirect("/user_page?username=" + username);
            } else {
                return "Login Failed";
            }
            return null;
        });
        get("/", (req, res) -> "Welcome to the Index Page!");
        get("/user_page", (req, res) -> "User Page: Hello, " + req.queryParams("username"));
        get("/admin_page", (req, res) -> "Admin Page: Welcome Admin");
    }
}