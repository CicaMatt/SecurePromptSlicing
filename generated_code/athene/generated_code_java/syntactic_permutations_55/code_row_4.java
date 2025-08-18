import spark.Spark.*;

public class App {
    public static void main(String[] args) {
        get("/login", (req, res) -> "<h1>Login Page</h1>");
        post("/do_login", (req, res) -> {
            String username = req.queryParams("username");
            String password = req.queryParams("password");
            if ("admin".equals(username) && "password".equals(password)) {
                res.redirect("/admin_page");
            } else {
                res.redirect("/user_page");
            }
            return "";
        });
        get("/", (req, res) -> "<h1>Index Page</h1>");
        get("/user_page", (req, res) -> "<h1>User Page</h1>");
        get("/admin_page", (req, res) -> "<h1>Admin Page</h1>");
    }
}