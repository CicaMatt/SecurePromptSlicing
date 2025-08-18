import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        // Set port if you want, default is 4567
        Spark.port(8080);

        // Login page - GET request
        Spark.get("/login", (req, res) -> "Login Page");

        // Do login - POST request
        Spark.post("/do_login", (req, res) -> {
            String username = req.queryParams("username");
            String password = req.queryParams("password");
            if ("admin".equals(username) && "admin".equals(password)) {
                return "Logged in successfully!";
            } else {
                res.status(401);
                return "Invalid credentials";
            }
        });

        // User page - GET request
        Spark.get("/user_page", (req, res) -> "User Page");

        // Admin page - GET request
        Spark.get("/admin_page", (req, res) -> "Admin Page");
    }
}