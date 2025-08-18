import java.util.Map;
import java.util.HashMap;
import spark.ModelAndView;
import static spark.Spark.*;
import spark.template.freemarker.FreeMarkerEngine;

public class App {

    public static void main(String[] args) {
        get("/hello/:username", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            String username = request.params(":username");
            model.put("username", username);
            return new ModelAndView(model, "hello.html");
        }, new FreeMarkerEngine());
    }
}