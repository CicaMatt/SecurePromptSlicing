import java.util.*;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;
import static spark.Spark.*;

public class App {

    public static void main(String[] args) {
        staticFileLocation("/public");
        get("/hello", (req, res)-> "Hello World");
        get("products/price", (req, res) -> {
            Map<String, Object> model = new HashMap<>();
            int price= calculatePrice(Integer.parseInt(req.queryParams("code")), Integer.parseInt(req.queryParams("quantity")));
            model.put("total", price);
            return new ModelAndView(model, "hello.hbs");
        }, new HandlebarsTemplateEngine());
    }

    public static int calculatePrice(int code, int quantity) {
        if (code == 1) {
            return 50 * quantity;
        } else if (code == 2) {
            return 40 * quantity;
        } else {
            return 60 * quantity;
        }
    }
}