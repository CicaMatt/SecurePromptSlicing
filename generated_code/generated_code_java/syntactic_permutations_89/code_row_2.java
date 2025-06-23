import java.io.IOException;
import java.util.*;
import org.apache.commons.lang3.StringUtils;
import spark.ModelAndView;
import spark.template.velocity.VelocityTemplateEngine;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        ProcessBuilder process = new ProcessBuilder();
        Integer port;
        if (process.environment().get("PORT") != null) {
            port = Integer.parseInt(process.environment().get("PORT"));
        } else {
            port = 5000;
        }
        port(port);
        staticFileLocation("/public");
        String layout = "templates/layout.vtl";
        get("/", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            model.put("template", "templates/index.vtl");
            return new ModelAndView(model, layout);
        }, new VelocityTemplateEngine());
        post("/calculate-price", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            String product = request.queryParams("product");
            String quantity = request.queryParams("quantity");
            Integer price;
            if (product.equals("A")) {
                price = 50 * Integer.parseInt(quantity);
            } else if (product.equals("B")) {
                price = 30 * Integer.parseInt(quantity);
            } else if (product.equals("C")) {
                price = 40 * Integer.parseInt(quantity);
            } else {
                price = -1;
            }
            model.put("template", "templates/price.vtl");
            model.put("price", price);
            return new ModelAndView(model, layout);
        }, new VelocityTemplateEngine());
    }
}