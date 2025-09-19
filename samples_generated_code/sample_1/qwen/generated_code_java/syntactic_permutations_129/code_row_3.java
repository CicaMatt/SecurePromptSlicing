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

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/", new HomeRoute());
    }

    static class Environment {
        private Configuration cfg;

        public Environment() {
            cfg = new Configuration(Configuration.VERSION_2_3_30);
            cfg.setClassForTemplateLoading(WebApp.class, "/templates");
        }

        public Template getTemplate(String name) throws Exception {
            return cfg.getTemplate(name + ".ftl");
        }
    }

    static class HomeRoute implements Route {

        private Environment env = new Environment();

        @Override
        public Object handle(Request request, Response response) {
            return renderResponseFromEnv(env, request);
        }

        private String renderResponseFromEnv(Environment env, Request request) {
            try {
                String name = request.queryParams("name");
                Template template = env.getTemplate("home");

                Map<String, Object> dataModel = new HashMap<>();
                dataModel.put("name", name);

                StringWriter out = new StringWriter();
                template.process(dataModel, out);
                return out.toString();

            } catch (Exception e) {
                response.status(500);
                return "Server Error";
            }
        }
    }
}