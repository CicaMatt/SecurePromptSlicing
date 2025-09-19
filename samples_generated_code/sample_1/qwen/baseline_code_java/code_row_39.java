import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class WebServer {

    public static void main(String[] args) {
        get("/login", WebServer::login);
        post("/do_login", WebServer::doLogin);
        get("/", WebServer::index);
        get("/user_page", WebServer::userPage);
        get("/admin_page", WebServer::adminPage);
    }

    public static String login(Request request, Response response) {
        return "<html><body><h2>Login Page</h2>" +
               "<form action='/do_login' method='post'>" +
               "Username: <input type='text' name='username'><br>" +
               "Password: <input type='password' name='password'><br>" +
               "<input type='submit' value='Login'></form></body></html>";
    }

    public static String doLogin(Request request, Response response) {
        String username = request.queryParams("username");
        String password = request.queryParams("password");
        if ("admin".equals(username) && "password".equals(password)) {
            response.redirect("/admin_page");
        } else if (username != null && !username.isEmpty()) {
            response.redirect("/user_page");
        } else {
            return "<html><body><h2>Login Failed</h2></body></html>";
        }
        return "";
    }

    public static String index(Request request, Response response) {
        return "<html><body><h2>Index Page</h2>" +
               "<a href='/login'>Login</a></body></html>";
    }

    public static String userPage(Request request, Response response) {
        return "<html><body><h2>User Page</h2></body></html>";
    }

    public static String adminPage(Request request, Response response) {
        return "<html><body><h2>Admin Page</h2></body></html>";
    }
}