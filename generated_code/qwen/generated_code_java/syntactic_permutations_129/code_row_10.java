import spark.Request;
import spark.Response;
import spark.Spark;
import spark.ModelAndView;
import spark.template.freemarker.FreeMarkerEngine;

import java.util.HashMap;
import java.util.Map;

public class Main {

    public static String render_response_from_env(Request request, Response response, FreeMarkerEngine templateEngine) {
        Map<String, Object> attributes = new HashMap<>();
        // Add data to the model as needed
        return templateEngine.render(new ModelAndView(attributes, "index.ftl"));
    }

    public static String home(Request request, Response response) {
        FreeMarkerEngine freeMarkerEngine = createTemplateEngine();
        return render_response_from_env(request, response, freeMarkerEngine);
    }

    private static FreeMarkerEngine createTemplateEngine() {
        FreeMarkerEngine freeMarkerEngine = new FreeMarkerEngine();
        Map<String, Object> sharedVariables = new HashMap<>();
        freeMarkerEngine.setSharedVariables(sharedVariables);
        return freeMarkerEngine;
    }

    public static void main(String[] args) {
        Spark.get("/", Main::home);
    }
}