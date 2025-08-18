import spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect", (req, res) -> {
            String target = req.queryParams("target");
            String regex = ".*example\\.com.*";
            if (target.matches(regex)) {
                res.redirect(target);
            } else {
                res.redirect("/");
            }
            return null;
        });
    }
}