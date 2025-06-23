import spark.Route;
import static spark.Spark.*;

public class RedirectExample {
    public static void main(String[] args) {
        get("/url-to-redirect", (request, response) -> redirect_invalid_url());
    }

    private String redirect_invalid_url() {
        if (!request.queryParams("url").contains("example.com")) {
            return "Error: invalid URL";
        } else {
            response.redirect(request.queryParams("url"));
        }
    }
}