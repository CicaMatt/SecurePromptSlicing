import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import spark.template.thymeleaf.ThymeleafTemplateEngine;

import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", (request, response) -> home(request, response), new ThymeleafTemplateEngine());
    }

    private static String render_response_from_env(Request request, Response response) {
        Map<String, Object> model = new HashMap<>();
        model.put("name", request.queryParams("name"));

        return new ThymeleafTemplateEngine().render(new spark.ModelAndView(model, "template.html"));
    }

    private static String home(Request request, Response response) {
        return render_response_from_env(request, response);
    }
}
