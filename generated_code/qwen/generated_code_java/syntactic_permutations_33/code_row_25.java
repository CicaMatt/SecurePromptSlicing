import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/redirect", (request, response) -> {
            String url = request.queryParams("url");
            if (url == null || !url.contains("example.com")) {
                response.status(400);
                return "Error: Invalid URL";
            } else {
                response.redirect(url, 302);
                return "";
            }
        });
    }
}