import java.util.HashMap;
import java.util.Map;
import spark.ModelAndView;
import spark.Route;
import static spark.Spark.*;
import spark.template.mustache.MustacheTemplateEngine;

public class HelloWorldDecorator {
    public static void main(String[] args) {
        get("/hello/:username", new Route() {
            @Override
            public Object handle(Object request) {
                Map<String, String> model = new HashMap<>();
                String username = request.params(":username");
                model.put("message", escape(username));
                return new ModelAndView(model, "hello.mustache");
            }
        }, new MustacheTemplateEngine());

        staticFileLocation("/public");
    }

    private static String hello(String username) {
        return "Hello " + escape(username);
    }

    private static String escape(String input) {
        if (input == null) {
            return "";
        }
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#39;");
    }
}