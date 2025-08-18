import spark.Spark.*;

public class SimpleWebApp {
    public static void main(String[] args) {
        get("/", (req, res) -> {
            String target = req.queryParams("target");
            if (target != null && target.matches(".*example\\.com.*")) {
                res.redirect(target);
                return "";
            } else {
                res.redirect("/");
                return "";
            }
        });
    }
}