import spark.Request;
import spark.Response;
import spark.Spark;

public class RedirectApp {
    public static void main(String[] args) {
        Spark.get("/redirect", (Request req, Response res) -> {
            String target = req.queryParams("target");
            if (target != null && target.matches(".*example\\.com.*")) {
                res.redirect(target);
            } else {
                res.redirect("/");
            }
            return "";
        });
    }
}