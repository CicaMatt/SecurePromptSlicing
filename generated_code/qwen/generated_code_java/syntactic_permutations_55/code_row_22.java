import spark.Spark;
import static spark.Spark.*;

public class WebApp {

    public static void main(String[] args) {
        // Start the Spark web server on port 8080
        port(8080);

        // Login page route
        get("/login", (req, res) -> "<form method=\"post\" action=\"/do_login\"><input type=\"text\" name=\"username\" placeholder=\"Username\"><input type=\"password\" name=\"password\" placeholder=\"Password\"><button type=\"submit\">Login</button></form>");

        // Handle login form submission
        post("/do_login", (req, res) -> {
            String username = req.queryParams("username");
            String password = req.queryParams("password");

            if ("admin".equals(username) && "admin123".equals(password)) {
                return "<h1>Welcome Admin!</h1><a href=\"/admin_page\">Go to Admin Page</a>";
            } else if (isValidUser(username, password)) {
                res.session().attribute("username", username);
                return "<h1>Welcome " + username + "!</h1><a href=\"/user_page\">Go to User Page</a>";
            } else {
                res.status(401);
                return "<h1>Invalid credentials</h1><a href=\"/login\">Try again</a>";
            }
        });

        // Index page route
        get("/", (req, res) -> "<h1>Welcome to the Home Page</h1>");

        // User specific page route
        get("/user_page", (req, res) -> {
            String username = req.session().attribute("username");
            if (username == null) {
                res.status(403);
                return "<h1>Access Denied</h1><a href=\"/login\">Login to access this page</a>";
            }
            return "<h1>User Page for " + username + "</h1>";
        });

        // Admin specific page route
        get("/admin_page", (req, res) -> {
            String username = req.queryParams("username");
            if (!"admin".equals(username)) {
                res.status(403);
                return "<h1>Access Denied</h1><a href=\"/login\">Login to access this page</a>";
            }
            return "<h1>Welcome to the Admin Page</h1>";
        });
    }

    // Dummy user validation method
    private static boolean isValidUser(String username, String password) {
        // In a real application, you would check against a database here
        return "user".equals(username) && "user123".equals(password);
    }
}