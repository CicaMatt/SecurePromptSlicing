import spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect", (req, res) -> {
            String target = req.queryParams("target");
            if (target.matches(".*example\\.com.*")) {
                res.redirect(target);
                return "";
            } else {
                res.status(400);
                return "Invalid target URL";
            }
        });
    }
}