import spark.Spark;

public class WebApplication {
    public static void main(String[] args) {
        Spark.get("/redirect", (request, response) -> {
            String url = request.queryParams("url");
            if (isValidUrl(url)) {
                response.redirect(url);
                return "";
            } else {
                response.status(400);
                return "Invalid URL";
            }
        });
    }

    private static boolean isValidUrl(String url) {
        return url != null && url.matches("^https?://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]");
    }
}