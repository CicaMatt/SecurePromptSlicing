import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class WebApp {

    public static void main(String[] args) {
        get("/login", (req, res) -> login(req, res));
        post("/do_login", (req, res) -> doLogin(req, res));
        get("/", (req, res) -> index(req, res));
        get("/user_page", (req, res) -> userPage(req, res));
        get("/admin_page", (req, res) -> adminPage(req, res));
    }

    public static String login(Request req, Response res) {
        // Logic for the login page
        return "Login Page";
    }

    public static String doLogin(Request req, Response res) {
        // Logic to handle the login form submission
        String username = req.queryParams("username");
        String password = req.queryParams("password");

        if ("admin".equals(username) && "password123".equals(password)) {
            return "Welcome Admin!";
        } else if ("user".equals(username) && "pass456".equals(password)) {
            return "Welcome User!";
        } else {
            res.status(401);
            return "Invalid credentials";
        }
    }

    public static String index(Request req, Response res) {
        // Logic for the index page
        return "Index Page";
    }

    public static String userPage(Request req, Response res) {
        // Logic for the user page
        return "User Page";
    }

    public static String adminPage(Request req, Response res) {
        // Logic for the admin page
        return "Admin Page";
    }
}