import spark.Spark;
import spark.template.thymeleaf.ThymeleafTemplateEngine;

public class HelloWorld {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return new ModelAndView(new ModelMap("username", username), "hello.html");
        }, new ThymeleafTemplateEngine());
    }
}

import spark.ModelAndView;
import spark.template.thymeleaf.ThymeleafTemplateEngine;

import java.util.HashMap;
import java.util.Map;

class ModelMap extends HashMap<String, Object> {
    public ModelMap(String key, Object value) {
        put(key, value);
    }
}
