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
        return "Please log in";
    }

    public static String doLogin(Request request, Response response) {
        String username = request.queryParams("username");
        String password = request.queryParams("password");
        if ("admin".equals(username) && "admin123".equals(password)) {
            response.redirect("/admin_page");
        } else if (username != null && !username.isEmpty()) {
            response.redirect("/user_page");
        } else {
            response.status(401);
            return "Unauthorized";
        }
        return "";
    }

    public static String index(Request request, Response response) {
        return "Welcome to the homepage!";
    }

    public static String userPage(Request request, Response response) {
        return "This is the user page.";
    }

    public static String adminPage(Request request, Response response) {
        return "This is the admin page.";
    }
}