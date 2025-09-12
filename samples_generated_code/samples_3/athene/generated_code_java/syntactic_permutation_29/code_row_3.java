import spark.Spark.*;

public class SimpleWebApp {
    public static void main(String[] args) {
        get("/redirect", (req, res) -> {
            String target = req.queryParams("target");
            if (target.matches(".*example\\.com.*")) {
                res.redirect(target);
            } else {
                res.redirect("/");
            }
            return null;
        });

        get("/", (req, res) -> "Welcome to the home page!");
    }
}