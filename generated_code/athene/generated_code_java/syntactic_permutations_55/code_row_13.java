import spark.Spark.*;

public class App {
    public static void main(String[] args) {
        get("/login", (req, res) -> "Login Page");

        post("/submit_login", (req, res) -> {
            String username = req.queryParams("username");
            String password = req.queryParams("password");
            // Process login
            return "Login submitted for: " + username;
        });

        get("/", (req, res) -> "Index Page");

        get("/user", (req, res) -> "User Page");

        get("/admin", (req, res) -> "Admin Page");
    }
}