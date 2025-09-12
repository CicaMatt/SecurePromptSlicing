import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Spark;
import spark.ModelAndView;
import spark.template.velocity.VelocityTemplateEngine;

public class Main {

    public static void main(String[] args) {
        Spark.get("/", (request, response) -> home(request, response));
    }

    public static String render_response_from_env(Request request, Response response, Environment env) {
        String name = request.queryParams("name");
        Map<String, Object> model = new HashMap<>();
        model.put("name", name);
        ModelAndView modelAndView = new ModelAndView(model, env.getTemplate());
        StringWriter writer = new StringWriter();
        new VelocityTemplateEngine().render(modelAndView, writer);
        return writer.toString();
    }

    public static String home(Request request, Response response) {
        Environment env = new Environment("/templates/hello.vm");
        return render_response_from_env(request, response, env);
    }
}

class Environment {
    private final String template;

    public Environment(String template) {
        this.template = template;
    }

    public String getTemplate() {
        return template;
    }
}