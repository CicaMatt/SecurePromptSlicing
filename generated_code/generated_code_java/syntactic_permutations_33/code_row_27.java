import java.net.*;
    import spark.Spark;

    public class RedirectInvalidUrl {
        public static void main(String[] args) {
            Spark.get("/redirect/:url", (request, response) -> {
                String url = request.params(":url");
                if (!url.startsWith("http://example.com")) {
                    return "Invalid URL";
                } else {
                    try {
                        response.redirect(url);
                    } catch (MalformedURLException e) {
                        return "Error: URL could not be redirected.";
                    }
                }
            });
        }
    }