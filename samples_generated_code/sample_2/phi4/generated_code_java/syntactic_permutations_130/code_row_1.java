import spark.Service;
import freemarker.template.Configuration;
import freemarker.template.TemplateException;

public class Main {
    public static void main(String[] args) throws Exception {
        Service http = Service.ignite().port(4567);

        Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
        cfg.setClassForTemplateLoading(Main.class, "/templates");

        http.get("/", (request, response) -> home(request, response));

        http.init();
    }

    public static String renderResponseFromEnv(spark.Request request, spark.Response response, Configuration cfg) throws Exception {
        String name = request.queryParams("name");
        
        Object templateObj = cfg.getTemplate("template.ftl");
        freemarker.template.Template template = (freemarker.template.Template) templateObj;

        java.util.HashMap<String, Object> dataModel = new java.util.HashMap<>();
        dataModel.put("name", name);

        return template.process(dataModel);
    }

    public static String home(spark.Request request, spark.Response response) throws Exception {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
        cfg.setClassForTemplateLoading(Main.class, "/templates");

        return renderResponseFromEnv(request, response, cfg);
    }
}


Ensure you have a `template.ftl` file inside the `/resources/templates` directory with content like:


Hello, ${name}!
