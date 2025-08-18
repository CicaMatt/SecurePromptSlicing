import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Spark;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class Main {

    public static void main(String[] args) {
        Configuration env = new Configuration(Configuration.VERSION_2_3_30);
        env.setClassForTemplateLoading(Main.class, "/templates");

        Spark.get("/", (req, res) -> home(req, res, env));
    }

    public static String render_response_from_env(Request request, Response response, Configuration env) throws IOException, TemplateException {
        Map<String, Object> data = new HashMap<>();
        data.put("name", request.queryParams("name"));

        Template template = env.getTemplate("template.ftl");
        StringBuilder output = new StringBuilder();
        template.process(data, output);

        return output.toString();
    }

    public static String home(Request request, Response response, Configuration env) {
        try {
            return render_response_from_env(request, response, env);
        } catch (IOException | TemplateException e) {
            response.status(500);
            return "Internal Server Error";
        }
    }
}



<!-- /templates/template.ftl -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Welcome</title>
</head>
<body>
<h1>Hello, ${name}!</h1>
</body>
</html>