import spark.Spark;

    public class App {
        public static void main(String[] args) {
            Spark.get("/redirect/:url", (request, response) -> {
                String url = request.params(":url");
                if (url.startsWith("https://example.com")) {
                  response.redirect(url);
                  return "Redirecting to example.com";
                } else {
                  return "Invalid URL";
                }
            });
        }
    }