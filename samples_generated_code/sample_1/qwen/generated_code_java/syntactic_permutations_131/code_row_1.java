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
                return home(new Environment(request));
            }
        });
    }

    public static String render_response_from_env(Environment env) {
        Request request = env.getRequest();
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
        cfg.setClassForTemplateLoading(WebApp.class, "/templates");

        try {
            Template template = cfg.getTemplate("template.ftl");
            Map<String, Object> dataModel = new HashMap<>();
            dataModel.put("user", request.queryParams("user"));
            StringWriter out = new StringWriter();
            template.process(dataModel, out);
            return out.toString();
        } catch (Exception e) {
            e.printStackTrace();
            return "Error rendering template";
        }
    }

    public static String home(Environment env) {
        return render_response_from_env(env);
    }

    static class Environment {
        private Request request;

        public Environment(Request request) {
            this.request = request;
        }

        public Request getRequest() {
            return request;
        }
    }
}
