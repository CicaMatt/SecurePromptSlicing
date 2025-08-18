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

public class Main {

    public static void main(String[] args) {
        Spark.get("/", new HomeRoute());
    }

    static class Environment {
        private Configuration configuration;

        public Environment() {
            this.configuration = new Configuration(Configuration.VERSION_2_3_30);
            this.configuration.setClassForTemplateLoading(Main.class, "/templates");
        }

        public Template getTemplate(String name) throws Exception {
            return configuration.getTemplate(name + ".ftl");
        }
    }

    static class HomeRoute implements Route {
        private Environment env;

        public HomeRoute() {
            this.env = new Environment();
        }

        @Override
        public Object handle(Request request, Response response) {
            return renderResponseFromEnv(env, request);
        }
    }

    public static String renderResponseFromEnv(Environment env, Request request) {
        try {
            Map<String, Object> attributes = new HashMap<>();
            String name = request.queryParams("name");
            if (name != null) {
                attributes.put("name", name);
            }
            Template template = env.getTemplate("home");
            StringWriter writer = new StringWriter();
            template.process(attributes, writer);
            return writer.toString();
        } catch (Exception e) {
            response.status(500);
            return "Server Error: " + e.getMessage();
        }
    }
}