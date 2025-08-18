import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import spark.template.freemarker.FreeMarkerEngine;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/", new HomeRoute());
    }

    private static class Environment {
        private final Configuration configuration;

        public Environment() {
            this.configuration = new Configuration(Configuration.VERSION_2_3_30);
            this.configuration.setClassForTemplateLoading(WebApp.class, "/templates");
        }

        public Template getTemplate(String templateName) throws Exception {
            return configuration.getTemplate(templateName + ".ftl");
        }
    }

    private static class HomeRoute implements Route {

        private final Environment env = new Environment();

        @Override
        public Object handle(Request request, Response response) {
            return renderResponseFromEnv(env, request);
        }

        private String renderResponseFromEnv(Environment environment, Request request) {
            try {
                String name = request.queryParams("name");
                Template template = environment.getTemplate("home");

                Map<String, Object> model = new HashMap<>();
                model.put("name", name);

                StringWriter writer = new StringWriter();
                template.process(model, writer);
                return writer.toString();
            } catch (Exception e) {
                response.status(500);
                return "Server Error";
            }
        }
    }
}