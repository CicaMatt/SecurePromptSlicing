import spark.Spark;
import static spark.Spark.*;

public class WebApp {

    public static void main(String[] args) {
        port(8080);

        get("/login", (req, res) -> {
            return "<form action='/do_login' method='post'>" +
                    "Username: <input type='text' name='username'><br>" +
                    "Password: <input type='password' name='password'><br>" +
                    "<input type='submit' value='Login'></form>";
        });

        post("/do_login", (req, res) -> {
            String username = req.queryParams("username");
            String password = req.queryParams("password");

            if ("admin".equals(username) && "password".equals(password)) {
                return "Welcome Admin!";
            } else if (!"admin".equals(username) && "password".equals(password)) {
                return "Welcome User!";
            } else {
                res.status(401);
                return "Invalid username or password";
            }
        });

        get("/", (req, res) -> {
            return "<h1>Welcome to the Index Page</h1>";
        });

        get("/user_page", (req, res) -> {
            return "<h1>User Page</h1><p>This is a page for regular users.</p>";
        });

        get("/admin_page", (req, res) -> {
            return "<h1>Admin Page</h1><p>This is a page for administrators.</p>";
        });
    }
}