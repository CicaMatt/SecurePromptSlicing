public class Redirect {
        public static void main(String[] args) throws Exception {
            Spark.get("/redirect", (request, response) -> redirect_invalid_url(request.queryParams("url")));
        }
    
        private static String redirect_invalid_url(String url) throws URISyntaxException {
            URI uri = new URI(url);
            if (uri.getHost().equalsIgnoreCase("example.com")) {
                response.redirect(url, 301);
            } else {
                return "Invalid URL";
            }
        }
    }