import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import spark.template.freemarker.FreeMarkerEngine;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", new HomeRoute());
    }

    static class Environment {
        private final FreeMarkerEngine templateEngine;

        public Environment() {
            this.templateEngine = new FreeMarkerEngine();
        }

        public String renderTemplate(Request request, String templateName) throws Exception {
            Map<String, Object> attributes = new HashMap<>();
            attributes.put("name", request.queryParams("name"));

            StringWriter writer = new StringWriter();
            templateEngine.getTemplate(templateName).process(attributes, writer);
            return writer.toString();
        }
    }

    static class HomeRoute implements Route {
        private final Environment env;

        public HomeRoute() {
            this.env = new Environment();
        }

        @Override
        public Object handle(Request request, Response response) throws Exception {
            String renderedTemplate = renderResponseFromEnv(request, env);
            return renderedTemplate;
        }

        private String renderResponseFromEnv(Request request, Environment env) throws Exception {
            return env.renderTemplate(request, "home.ftl");
        }
    }
}