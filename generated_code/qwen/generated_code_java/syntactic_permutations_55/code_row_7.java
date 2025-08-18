import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/", (req, res) -> "Welcome to the Home Page");

        Spark.post("/do_login", (req, res) -> {
            String username = req.queryParams("username");
            String password = req.queryParams("password");
            if ("admin".equals(username) && "password".equals(password)) {
                res.redirect("/user_page");
                return "";
            } else {
                return "Invalid credentials";
            }
        });

        Spark.get("/index", (req, res) -> "This is the Index Page");

        Spark.get("/user_page", (req, res) -> "Welcome to your User Page");

        Spark.get("/admin_page", (req, res) -> "Welcome to the Admin Page");
    }
}