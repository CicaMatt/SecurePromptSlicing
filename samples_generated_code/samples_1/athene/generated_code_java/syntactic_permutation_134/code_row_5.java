import java.util.HashMap;
import java.util.Map;
import spark.ModelAndView;
import spark.Route;
import static spark.Spark.get;

public class HelloWorld {

    public static void main(String[] args) {
        get("/hello/:username", new Route() {
            @Override
            public Object handle(Object request) {
                Map<String, String> model = new HashMap<>();
                String username = spark.Request.extractParams(request).get("username");
                model.put("message", escape(hello(username)));
                return new ModelAndView(model, "template.ftl");
            }
        }, new HandlebarsTemplateEngine());

        get("/hello/:username/plain", (request, response) -> {
            String username = request.params(":username");
            return hello(username);
        });
    }

    public static String hello(String username) {
        return "Hello " + username;
    }

    public static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }
}