import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.mustache.MustacheTemplateEngine;

import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", (request, response) -> home(request, response));
    }

    private static String render_response_from_env(Request request, Response response) {
        Map<String, Object> model = new HashMap<>();
        String name = request.queryParams("name");
        if (name == null) {
            name = "World";
        }
        model.put("name", name);
        return new MustacheTemplateEngine().render(new ModelAndView(model, "template.mustache"));
    }

    private static String home(Request request, Response response) {
        return render_response_from_env(request, response);
    }
}