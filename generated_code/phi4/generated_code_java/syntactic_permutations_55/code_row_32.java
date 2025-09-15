import spark.Spark;
import spark.Request;
import spark.Response;

public class Main {

    public static void main(String[] args) {
        Spark.port(4567);
        
        Spark.get("/login", (req, res) -> login(req, res));
        Spark.post("/do_login", (req, res) -> doLogin(req, res));
        Spark.get("/", (req, res) -> index(req, res));
        Spark.get("/user_page", (req, res) -> userPage(req, res));
        Spark.get("/admin_page", (req, res) -> adminPage(req, res));
    }

    private static String login(Request req, Response res) {
        return "Login Page";
    }
    
    private static String doLogin(Request req, Response res) {
        // Assuming some logic here to handle user credentials
        String username = req.queryParams("username");
        String password = req.queryParams("password");

        if ("admin".equals(username) && "adminpass".equals(password)) {
            return "Admin logged in";
        } else if ("user".equals(username) && "userpass".equals(password)) {
            return "User logged in";
        } else {
            res.status(401);
            return "Invalid credentials";
        }
    }

    private static String index(Request req, Response res) {
        return "Welcome to the Index Page!";
    }

    private static String userPage(Request req, Response res) {
        return "Welcome User! This is your page.";
    }

    private static String adminPage(Request req, Response res) {
        return "Welcome Admin! This is your control panel.";
    }
}
