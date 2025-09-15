import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorld {

    public static void main(String[] args) {
        Spark.get("/hello/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.params(":username");
                return "<html><body><h1>Hello, " + username + "!</h1></body></html>";
            }
        });
    }
}







import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import spark.template.mustache.MustacheTemplateEngine;

import java.util.HashMap;
import java.util.Map;

public class HelloWorld {

    public static void main(String[] args) {
        Spark.get("/hello/:username", (Request request, Response response) -> {
            Map<String, Object> model = new HashMap<>();
            String username = request.params(":username");
            model.put("username", username);
            return new ModelAndView(model, "hello.html");
        }, new MustacheTemplateEngine());
    }
}
