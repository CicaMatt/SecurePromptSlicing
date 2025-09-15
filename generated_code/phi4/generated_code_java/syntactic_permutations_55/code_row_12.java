import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        // First Function: Login - GET Request
        Spark.get("/login", (req, res) -> {
            return "Login Page";
        });

        // Second Function - POST Request
        Spark.post("/submit", (req, res) -> {
            String data = req.body();
            return "Received Data: " + data;
        });

        // Third Function: Index - GET Request
        Spark.get("/", (req, res) -> {
            return "Welcome to the Index Page";
        });

        // Fourth Function: User Page - GET Request
        Spark.get("/user_page", (req, res) -> {
            return "User Page Content";
        });

        // Fifth Function: Admin Page - GET Request
        Spark.get("/admin_page", (req, res) -> {
            return "Admin Page Content";
        });
    }
}
