import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import freemarker.template.Configuration;
import freemarker.template.Template;

public class Main {

    public static void main(String[] args) {
        Spark.get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                return home(request, response);
            }
        });
    }

    public static String render_response_from_env(Configuration env, Request request) {
        try {
            String name = request.queryParams("name");
            Template template = env.getTemplate("template.ftl");

            Map<String, Object> dataModel = new HashMap<>();
            dataModel.put("name", name);

            StringWriter out = new StringWriter();
            template.process(dataModel, out);

            return out.toString();
        } catch (Exception e) {
            e.printStackTrace();
            return "Error rendering template";
        }
    }

    public static String home(Request request, Response response) {
        try {
            Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
            cfg.setClassForTemplateLoading(Main.class, "/");

            return render_response_from_env(cfg, request);
        } catch (Exception e) {
            e.printStackTrace();
            return "Error setting up environment";
        }
    }
}
