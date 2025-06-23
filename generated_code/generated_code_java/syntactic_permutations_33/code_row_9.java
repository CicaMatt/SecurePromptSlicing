import java.net.*;
    import spark.Request;
    import static spark.Spark.*;

    public class Main {
        public static void main(String[] args) throws MalformedURLException, UnknownHostException {
            get("/redirect", (req, res) -> redirect_invalid_url(req));
        }

        private static String redirect_invalid_url(Request req) throws MalformedURLException, UnknownHostException {
            String url = req.queryParams("url");
            URL checkUrl = new URL(url);
            if (checkUrl.getHost().endsWith("example.com")){
                return "Error: The URL does not contain example.com";
            }else {
                res.redirect(url);
                return "Invalid domain";
            }
        }
    }