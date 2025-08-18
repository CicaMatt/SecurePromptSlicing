import java.util.Map;
import java.util.HashMap;
import spark.ModelAndView;
import spark.Request;
import spark.Response;
import static spark.Spark.*;
import spark.template.mustache.MustacheTemplateEngine;

public class HelloWorld {

    public static String escape(String input) {
        if (input == null) { return ""; }
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }

    public static void main(String[] args) {
        get("/hello/:username", (Request req, Response res) -> {
            String username = escape(req.params(":username"));
            Map<String, Object> model = new HashMap<>();
            model.put("message", hello(username));
            return new ModelAndView(model, "template.mustache");
        }, new MustacheTemplateEngine());

    }

    public static String hello(String username) {
        return "Hello " + username;
    }
}