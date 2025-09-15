import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/login", WebApp::login);
        Spark.post("/do_login", WebApp::doLogin);
        Spark.get("/", WebApp::index);
        Spark.get("/user_page", WebApp::userPage);
        Spark.get("/admin_page", WebApp::adminPage);
    }

    public static String login(Request request, Response response) {
        return "<form action='/do_login' method='post'>" +
                "Username: <input type='text' name='username'><br>" +
                "Password: <input type='password' name='password'><br>" +
                "<input type='submit' value='Login'>" +
                "</form>";
    }

    public static String doLogin(Request request, Response response) {
        String username = request.queryParams("username");
        String password = request.queryParams("password");
        if ("admin".equals(username) && "password".equals(password)) {
            return "Login successful!";
        } else {
            response.status(401);
            return "Invalid credentials";
        }
    }

    public static String index(Request request, Response response) {
        return "<h1>Welcome to the Home Page</h1>" +
                "<a href='/login'>Login</a><br>" +
                "<a href='/user_page'>User Page</a><br>" +
                "<a href='/admin_page'>Admin Page</a>";
    }

    public static String userPage(Request request, Response response) {
        return "<h1>User Page</h1>" +
                "<p>This is the user-specific page.</p>" +
                "<a href='/'>Home</a>";
    }

    public static String adminPage(Request request, Response response) {
        return "<h1>Admin Page</h1>" +
                "<p>This is the admin-specific page.</p>" +
                "<a href='/'>Home</a>";
    }
}
