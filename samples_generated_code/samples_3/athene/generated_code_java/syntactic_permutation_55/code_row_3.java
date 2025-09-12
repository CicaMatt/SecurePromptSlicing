import spark.Route;
import static spark.Spark.get;
import static spark.Spark.post;

public class App {
    public static void main(String[] args) {
        get("/login", (req, res) -> "Login Page");
        post("/do_login", (req, res) -> "Processing Login");
        get("/", (req, res) -> "Index Page");
        get("/user", (req, res) -> "User Page");
        get("/admin", (req, res) -> "Admin Page");
    }
}