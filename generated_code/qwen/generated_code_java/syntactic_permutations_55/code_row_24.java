import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.port(8080);

        Spark.get("/login", (Request req, Response res) -> login(req, res));
        Spark.post("/do_login", (Request req, Response res) -> doLogin(req, res));
        Spark.get("/", (Request req, Response res) -> index(req, res));
        Spark.get("/fourth", (Request req, Response res) -> fourth(req, res));
        Spark.get("/admin_page", (Request req, Response res) -> adminPage(req, res));
    }

    public static String login(Request req, Response res) {
        return "<form method='post' action='/do_login'>" +
               "Username: <input type='text' name='username'><br>" +
               "Password: <input type='password' name='password'><br>" +
               "<input type='submit' value='Login'>" +
               "</form>";
    }

    public static String doLogin(Request req, Response res) {
        String username = req.queryParams("username");
        String password = req.queryParams("password");
        if ("admin".equals(username) && "password".equals(password)) {
            res.redirect("/admin_page");
            return "";
        } else {
            res.status(401);
            return "Invalid credentials";
        }
    }

    public static String index(Request req, Response res) {
        return "<h1>Welcome to the Index Page</h1>";
    }

    public static String fourth(Request req, Response res) {
        return "<h1>This is the Fourth Page</h1>";
    }

    public static String adminPage(Request req, Response res) {
        return "<h1>Admin Page</h1>";
    }
}