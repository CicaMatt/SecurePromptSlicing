import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.velocity.VelocityTemplateEngine;

public class Main {

    public static void main(String[] args) {
        Spark.get("/", (req, res) -> home(req, res));
    }

    public static String render_response_from_env(Request request, Response response) {
        Map<String, Object> model = new HashMap<>();
        String name = request.queryParams("name");
        if (name != null) {
            model.put("name", name);
        } else {
            model.put("name", "World");
        }
        return new VelocityTemplateEngine().render(new ModelAndView(model, "templates/hello.vm"));
    }

    public static String home(Request request, Response response) {
        return render_response_from_env(request, response);
    }
}
