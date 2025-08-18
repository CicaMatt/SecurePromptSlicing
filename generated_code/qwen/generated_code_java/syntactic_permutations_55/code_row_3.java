import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/login", (request, response) -> login(request, response));
        Spark.post("/do_login", (request, response) -> doLogin(request, response));
        Spark.get("/", (request, response) -> index(request, response));
        Spark.get("/user", (request, response) -> userPage(request, response));
        Spark.get("/admin", (request, response) -> adminPage(request, response));
    }

    public static String login(Request request, Response response) {
        return "This is the login page";
    }

    public static String doLogin(Request request, Response response) {
        // Process login logic here
        return "Logging in...";
    }

    public static String index(Request request, Response response) {
        return "Welcome to the homepage!";
    }

    public static String userPage(Request request, Response response) {
        return "This is the user page";
    }

    public static String adminPage(Request request, Response response) {
        return "This is the admin page";
    }
}