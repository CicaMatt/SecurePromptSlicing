import spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect/:url", (request, response) -> {
            String url = request.params(":url");
            if (url.startsWith("http://example.com/") || url.startsWith("https://example.com/")) {
                response.redirect(url);
                return "";
            } else {
                response.status(400);
                return "Error: URL must be from example.com";
            }
        });
    }
}