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

    private static Configuration setupFreemarkerConfig() throws Exception {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(WebApp.class, "/templates");
        return cfg;
    }

    private static class HomeRoute implements Route {
        @Override
        public Object handle(Request request, Response response) throws Exception {
            Map<String, Object> env = new HashMap<>();
            env.put("templatePath", "home.ftl");
            return renderResponseFromEnv(request, env);
        }
    }

    private static String renderResponseFromEnv(Request request, Map<String, Object> env) throws Exception {
        Configuration cfg = setupFreemarkerConfig();
        Template template = cfg.getTemplate((String) env.get("templatePath"));
        String name = request.queryParams("name");
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);
        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        return out.toString();
    }
}