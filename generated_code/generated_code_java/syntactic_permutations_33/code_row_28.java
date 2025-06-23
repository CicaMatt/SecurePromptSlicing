import java.net.URI;
import spark.ModelAndView;
import spark.template.freemarker.FreeMarkerEngine;
import static spark.Spark.*;

public class HelloWorld {
    public static void main(String[] args) {
        get("/:url", (req, res) -> {
            String url = req.params(":url");
            URI uri = new URI(url);
            if ("example.com".equals(uri.getHost())) {
                return "Redirecting to " + url;
            } else {
                halt(401, "URL is not allowed.");
            }
        });
    }
}