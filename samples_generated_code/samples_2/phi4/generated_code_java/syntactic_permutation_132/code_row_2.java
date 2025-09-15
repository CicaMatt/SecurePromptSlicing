import static spark.Spark.*;
import com.sparktemplate.FreeMarkerTemplateEngine;
import java.io.IOException;

public class HelloApp {

    public static void main(String[] args) {
        port(4567);

        // Set up FreeMarker template engine
        FreeMarkerTemplateEngine templateEngine = new FreeMarkerTemplateEngine();

        get("/hello/:username", (req, res) -> {
            String username = req.params(":username");
            return templateEngine.render(new ModelAndView("views/hello.html", "username", username));
        }, templateEngine);
    }
}
