import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class Main {

    public static void main(String[] args) {
        Spark.get("/", new HomeRoute());
    }

    static class Environment {
        private Configuration cfg;

        public Environment() {
            cfg = new Configuration(Configuration.VERSION_2_3_30);
            cfg.setClassForTemplateLoading(Main.class, "/templates");
        }

        public String renderTemplate(String templateName, Map<String, Object> data) throws Exception {
            Template template = cfg.getTemplate(templateName + ".ftl");
            StringWriter stringWriter = new StringWriter();
            template.process(data, stringWriter);
            return stringWriter.toString();
        }
    }

    static class HomeRoute implements Route {

        private Environment env;

        public HomeRoute() {
            this.env = new Environment();
        }

        @Override
        public Object handle(Request request, Response response) throws Exception {
            return renderResponseFromEnv(request, response);
        }

        private String renderResponseFromEnv(Request request, Response response) throws Exception {
            String name = request.queryParams("name");
            Map<String, Object> data = new HashMap<>();
            data.put("name", name != null ? name : "World");

            return env.renderTemplate("hello", data);
        }
    }
}