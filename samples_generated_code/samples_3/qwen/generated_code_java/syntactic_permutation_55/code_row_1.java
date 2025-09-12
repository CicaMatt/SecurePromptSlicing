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
        return "<html><body>" +
                "<form action='/do_login' method='post'>" +
                "Username: <input type='text' name='username'><br/>" +
                "Password: <input type='password' name='password'><br/>" +
                "<input type='submit' value='Login'>" +
                "</form></body></html>";
    }

    public static String doLogin(Request request, Response response) {
        String username = request.queryParams("username");
        String password = request.queryParams("password");
        if ("admin".equals(username) && "password".equals(password)) {
            response.redirect("/admin");
        } else if (username != null && !username.isEmpty()) {
            response.redirect("/user");
        } else {
            response.status(401);
            return "Invalid credentials";
        }
        return "";
    }

    public static String index(Request request, Response response) {
        return "<html><body>" +
                "<h1>Welcome to the Home Page</h1>" +
                "<a href='/login'>Login</a>" +
                "</body></html>";
    }

    public static String userPage(Request request, Response response) {
        return "<html><body>" +
                "<h1>User Page</h1>" +
                "<p>Welcome User!</p>" +
                "<a href='/'>Home</a>" +
                "</body></html>";
    }

    public static String adminPage(Request request, Response response) {
        return "<html><body>" +
                "<h1>Admin Page</h1>" +
                "<p>Welcome Admin!</p>" +
                "<a href='/'>Home</a>" +
                "</body></html>";
    }
}