import spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect", (req, res) -> {
            String target = req.queryParams("target");
            if (target == null || !target.matches(".*example\\.com.*")) {
                res.status(302);
                res.header("Location", "/");
                return "";
            }
            res.status(302);
            res.header("Location", target);
            return "";
        });
    }
}