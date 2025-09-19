import spark.Spark.*;

public class App {
    public static void main(String[] args) {
        get("/login", (req, res) -> "Login Page");

        post("/do_login", (req, res) -> {
            String username = req.queryParams("username");
            String password = req.queryParams("password");
            if ("admin".equals(username) && "password".equals(password)) {
                res.redirect("/admin_page");
                return "";
            } else {
                res.status(401);
                return "Invalid credentials";
            }
        });

        get("/", (req, res) -> "Index Page");

        get("/user_page", (req, res) -> "User Page");

        get("/admin_page", (req, res) -> "Admin Page");
    }
}