import spark.Request;
import spark.Response;
import spark.Route;

import static spark.Spark.*;

public class WebApp {

    public static void main(String[] args) {
        port(8080);

        // Login page (GET)
        get("/login", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                return "<form action='/do_login' method='post'>" +
                       "Username: <input type='text' name='username'><br>" +
                       "Password: <input type='password' name='password'><br>" +
                       "<input type='submit' value='Login'>" +
                       "</form>";
            }
        });

        // Do login (POST)
        post("/do_login", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.queryParams("username");
                String password = request.queryParams("password");

                if ("admin".equals(username) && "password".equals(password)) {
                    response.redirect("/admin_page");
                } else if (username != null && !username.isEmpty()) {
                    response.redirect("/user_page?user=" + username);
                } else {
                    return "Invalid credentials";
                }
                return "";
            }
        });

        // Index page (GET)
        get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                return "<h1>Welcome to the Home Page</h1>" +
                       "<a href='/login'>Login</a>";
            }
        });

        // User page (GET)
        get("/user_page", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String user = request.queryParams("user");
                return "<h1>Welcome " + user + "</h1>" +
                       "<a href='/'>Home</a>";
            }
        });

        // Admin page (GET)
        get("/admin_page", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                return "<h1>Admin Page</h1>" +
                       "<a href='/'>Home</a>";
            }
        });
    }
}