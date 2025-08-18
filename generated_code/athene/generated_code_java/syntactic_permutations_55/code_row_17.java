import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        get("/login", (Request req, Response res) -> "Login Page");
        post("/do_login", (Request req, Response res) -> "Login Processed");
        get("/", (Request req, Response res) -> "Index Page");
        get("/user", (Request req, Response res) -> "User Page");
        get("/admin", (Request req, Response res) -> "Admin Page");
    }
}