import spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect", (req, res) -> {
            String target = req.queryParams("target");
            if (target.matches("^https?://[^/]+(/.*)?$")) {
                res.redirect(target);
            } else {
                res.redirect("/");
            }
            return "";
        });
    }
}