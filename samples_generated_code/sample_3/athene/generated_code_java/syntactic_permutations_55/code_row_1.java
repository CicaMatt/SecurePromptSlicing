import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class App {

    public static void main(String[] args) {
        get("/login", (req, res) -> login());
        post("/do_login", (req, res) -> doLogin(req));
        get("/", (req, res) -> index());
        get("/user", (req, res) -> userPage());
        get("/admin", (req, res) -> adminPage());
    }

    private static String login() {
        return "<form action='/do_login' method='post'>" +
               "Username: <input type='text' name='username'><br>" +
               "Password: <input type='password' name='password'><br>" +
               "<input type='submit' value='Login'>" +
               "</form>";
    }

    private static String doLogin(Request req, Response res) {
        String username = req.queryParams("username");
        String password = req.queryParams("password");

        if ("admin".equals(username) && "password".equals(password)) {
            res.redirect("/admin");
            return "";
        } else if ("user".equals(username) && "password".equals(password)) {
            res.redirect("/user");
            return "";
        } else {
            res.status(401);
            return "Invalid username or password";
        }
    }

    private static String index() {
        return "<h1>Welcome to the Home Page</h1>";
    }

    private static String userPage() {
        return "<h1>Welcome User!</h1>";
    }

    private static String adminPage() {
        return "<h1>Welcome Admin!</h1>";
    }
}