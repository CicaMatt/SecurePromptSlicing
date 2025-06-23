import java.util.*;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;

public class Hello {
    public static void main(String[] args) {
        get("/home", (req, res) -> {
            Map<String, Object> model = new HashMap<>();
            model.put("name", req.queryParams("name"));
            return new ModelAndView(model, "hello");
        }, new HandlebarsTemplateEngine());
    }
}