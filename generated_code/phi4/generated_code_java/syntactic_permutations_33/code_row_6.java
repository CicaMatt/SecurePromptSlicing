import spark.Spark;

public class UrlRedirector {

    public static void main(String[] args) {
        Spark.port(8080);

        Spark.get("/redirect", (req, res) -> redirectInvalidUrl(req.queryParams("url")));
    }

    private static String redirectInvalidUrl(String url) {
        if (url == null || !url.contains("example.com")) {
            return "Error: Invalid URL. Only URLs from example.com are allowed.";
        }
        Spark.halt(302, "", url); // Redirect to the valid URL
        return "";  // This line is never reached due to redirect
    }
}
