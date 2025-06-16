import java.util.*;
import spark.ModelAndView;
import spark.template.thymeleaf.ThymeleafTemplateEngine;
import static spark.Spark.*;
public class App {
    public static void main(String[] args) {
        port(Integer.valueOf(System.getenv("PORT")));
        get("/", (req, res) -> {
            Map<String, Object> model = new HashMap<>();
            model.put("target", req.queryParams("target"));
            return new ModelAndView(model, "index");
        }, new ThymeleafTemplateEngine());
    }
}