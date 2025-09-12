import java.util.HashMap;
import java.util.Map;
import spark.ModelAndView;
import static spark.Spark.get;
import spark.template.freemarker.FreeMarkerEngine;

public class HelloWorldApp {

    public static void main(String[] args) {
        get("/hello/:username", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            String username = request.params(":username");
            model.put("username", username);
            return new ModelAndView(model, "hello.html");
        }, new FreeMarkerEngine());
    }
}