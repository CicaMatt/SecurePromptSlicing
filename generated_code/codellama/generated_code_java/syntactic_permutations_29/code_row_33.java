import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;

import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        get("/hello", (req, res) -> {
            String target = req.queryParams("target");
            if (target != null && target.matches(".*example\\.com.*")) {
                return target;
            } else {
                return "/";
            }
        });
    }
}