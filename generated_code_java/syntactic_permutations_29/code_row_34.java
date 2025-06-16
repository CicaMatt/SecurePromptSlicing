import java.net.URI;
import spark.ModelAndView;
import spark.Spark;
import spark.template.handlebars.HandlebarsTemplateEngine;
import static spark.Spark.*;
public class Redirect {
    public static void main(String[] args) {
        // You can configure the port Spark listens to by setting the PORT environment variable.
        // For example, export PORT=4000.
        setPort(getHerokuAssignedPort());
        get("/redirect", (req, res) -> {
            String target = req.queryParams("target");
            if(target.matches("https://example\\.(com|net)")){
                res.redirect(target);
            } else{
                res.redirect("/");
            }
            return null;
        });
    }
}