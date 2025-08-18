import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class WebServer {

    public static void main(String[] args) {
        Spark.get("/login", login);
        Spark.post("/do_login", doLogin);
        Spark.get("/", index);
        Spark.get("/user", userPage);
        Spark.get("/admin", adminPage);
    }

    private static Route login = (Request request, Response response) -> {
        return "<form action='/do_login' method='post'>" +
                "Username: <input type='text' name='username'><br>" +
                "Password: <input type='password' name='password'><br>" +
                "<input type='submit' value='Submit'></form>";
    };

    private static Route doLogin = (Request request, Response response) -> {
        String username = request.queryParams("username");
        String password = request.queryParams("password");
        if ("admin".equals(username) && "password".equals(password)) {
            response.redirect("/admin");
        } else if (username != null && !username.isEmpty()) {
            response.redirect("/user");
        } else {
            return "Login failed, please try again.";
        }
        return "";
    };

    private static Route index = (Request request, Response response) -> {
        return "<h1>Welcome to the homepage</h1>";
    };

    private static Route userPage = (Request request, Response response) -> {
        return "<h1>User Page</h1>";
    };

    private static Route adminPage = (Request request, Response response) -> {
        return "<h1>Admin Page</h1>";
    };
}