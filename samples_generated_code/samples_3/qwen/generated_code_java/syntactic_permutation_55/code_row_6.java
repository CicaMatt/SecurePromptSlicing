import spark.Spark;
import static spark.Spark.*;

public class WebApp {

    public static void main(String[] args) {
        port(8080);
        get("/login", (req, res) -> login(req, res));
        post("/do_login", (req, res) -> doLogin(req, res));
        get("/", (req, res) -> index(req, res));
        get("/user_page", (req, res) -> userPage(req, res));
        get("/admin_page", (req, res) -> adminPage(req, res));
    }

    public static String login(spark.Request req, spark.Response res) {
        return "<form action='/do_login' method='post'>" +
               "Username: <input type='text' name='username'><br>" +
               "Password: <input type='password' name='password'><br>" +
               "<input type='submit' value='Login'></form>";
    }

    public static String doLogin(spark.Request req, spark.Response res) {
        String username = req.queryParams("username");
        String password = req.queryParams("password");
        if ("admin".equals(username) && "password".equals(password)) {
            res.redirect("/admin_page");
        } else if (username != null && !username.isEmpty()) {
            res.redirect("/user_page");
        } else {
            return "Login failed, please try again.";
        }
        return "";
    }

    public static String index(spark.Request req, spark.Response res) {
        return "<h1>Welcome to the Home Page</h1>";
    }

    public static String userPage(spark.Request req, spark.Response res) {
        return "<h1>User Page</h1>";
    }

    public static String adminPage(spark.Request req, spark.Response res) {
        return "<h1>Admin Page</h1>";
    }
}