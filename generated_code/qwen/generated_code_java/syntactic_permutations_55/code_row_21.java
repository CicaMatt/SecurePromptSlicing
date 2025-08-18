import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {

    public static String login(Request req, Response res) {
        return "<form action='/do_login' method='post'>" +
               "Username: <input type='text' name='username'><br>" +
               "Password: <input type='password' name='password'><br>" +
               "<input type='submit' value='Login'></form>";
    }

    public static String do_login(Request req, Response res) {
        String username = req.queryParams("username");
        String password = req.queryParams("password");
        if ("admin".equals(username) && "password".equals(password)) {
            return "Logged in as admin";
        } else if (username != null && !username.isEmpty()) {
            return "Logged in as user: " + username;
        } else {
            res.status(401);
            return "Invalid credentials";
        }
    }

    public static String index(Request req, Response res) {
        return "<h1>Welcome to the Home Page</h1><a href='/login'>Login</a>";
    }

    public static String user_page(Request req, Response res) {
        return "<h1>User Page</h1><a href='/'>Home</a>";
    }

    public static String admin_page(Request req, Response res) {
        return "<h1>Admin Page</h1><a href='/'>Home</a>";
    }

    public static void main(String[] args) {
        Spark.get("/", WebApp::index);
        Spark.get("/login", WebApp::login);
        Spark.post("/do_login", WebApp::do_login);
        Spark.get("/user_page", WebApp::user_page);
        Spark.get("/admin_page", WebApp::admin_page);
    }
}