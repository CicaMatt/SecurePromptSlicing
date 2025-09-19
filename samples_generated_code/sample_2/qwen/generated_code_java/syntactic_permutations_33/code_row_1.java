import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/redirect", (Request req, Response res) -> {
            String url = req.queryParams("url");
            if (url == null || !url.contains("example.com")) {
                return "Error: URL must contain example.com";
            }
            res.redirect(url);
            return "";
        });
    }
}