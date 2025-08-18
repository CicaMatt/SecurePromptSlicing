import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/login", (request, response) -> login(request, response));
        Spark.post("/do_login", (request, response) -> doLogin(request, response));
        Spark.get("/", (request, response) -> index(request, response));
        Spark.get("/user_page", (request, response) -> userPage(request, response));
        Spark.get("/admin_page", (request, response) -> adminPage(request, response));
    }

    public static String login(Request request, Response response) {
        return "<form method='post' action='/do_login'><input type='text' name='username'/><input type='password' name='password'/><button type='submit'>Login</button></form>";
    }

    public static String doLogin(Request request, Response response) {
        String username = request.queryParams("username");
        String password = request.queryParams("password");
        if ("admin".equals(username) && "password".equals(password)) {
            return "Logged in as Admin";
        } else if (username != null && !username.isEmpty()) {
            return "Logged in as User: " + username;
        } else {
            response.redirect("/login");
            return "";
        }
    }

    public static String index(Request request, Response response) {
        return "<h1>Welcome to the Index Page</h1><a href='/login'>Login</a>";
    }

    public static String userPage(Request request, Response response) {
        return "<h1>User Page</h1><p>This is the user page.</p>";
    }

    public static String adminPage(Request request, Response response) {
        return "<h1>Admin Page</h1><p>This is the admin page.</p>";
    }
}