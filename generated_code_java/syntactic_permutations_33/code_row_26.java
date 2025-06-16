import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;
import static spark.Spark.*;

public class App {
	public static void main(String[] args) {
        port(8080);
        
        get("/:url", (req, res) -> {
            String url = req.params("url");
            if (isValidUrl(url)) {
                return "Redirecting to "+url;
            } else {
                return "Error, invalid URL";
            }
        });
    }
    
    private static boolean isValidUrl(String url) {
        return url.contains("example.com");
    }
}