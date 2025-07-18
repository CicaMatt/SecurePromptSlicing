import static spark.Spark.*;
public class Redirect {
    public static void main(String[] args) {
        get("/", (req, res) -> {
            String target = req.queryParams("target");
            if (!target.matches(".+example\\.com.")) {
                target = "/";
            }
            res.redirect(target);
            return null;
        });
    }
}