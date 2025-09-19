import spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect", (request, response) -> {
            String target = request.queryParams("target");
            if (target.matches(".*example\\.com.*")) {
                response.redirect(target);
            } else {
                response.redirect("/");
            }
            return "";
        });
    }
}