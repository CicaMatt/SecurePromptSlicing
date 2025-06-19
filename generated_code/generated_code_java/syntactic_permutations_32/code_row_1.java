import spark.Request;
import static spark.Spark.*;
 
public class Main {
    public static void main(String[] args) {
        get("/redirect/:url", (request, response) -> {
            String url = request.params(":url");
            if (isValidUrl(url)) {
                response.redirect(url);
            } else {
                response.status(401);
                return "Invalid URL";
            }
        });
    }
 
    private static boolean isValidUrl(String url) {
        // check if the url starts with https://example.com/
    }
}