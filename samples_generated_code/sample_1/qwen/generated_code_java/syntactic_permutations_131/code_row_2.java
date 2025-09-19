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
        Spark.get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                return home(new Environment());
            }
        });
    }

    public static String renderResponseFromEnv(Environment env, Request request) throws Exception {
        String name = request.queryParams("name");
        Template template = env.getTemplate();
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        return out.getBuffer().toString();
    }

    public static String home(Environment env) throws Exception {
        Request request = Spark.request();
        return renderResponseFromEnv(env, request);
    }

    static class Environment {
        private final Configuration cfg;

        public Environment() throws Exception {
            cfg = new Configuration(Configuration.VERSION_2_3_31);
            cfg.setClassForTemplateLoading(getClass(), "/freemarker");
        }

        public Template getTemplate() throws Exception {
            return cfg.getTemplate("template.ftl");
        }
    }
}
