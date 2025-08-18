import java.io.IOException;
import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class TemplateRenderer {

    public static void main(String[] args) throws IOException, TemplateException {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(TemplateRenderer.class, "/");
        Map<String, Object> env = new HashMap<>();
        env.put("name", "World");
        Response response = home(env);
        System.out.println(response.getContent());
    }

    public static Response render_response_from_env(Map<String, Object> env) throws IOException, TemplateException {
        String name = (String) env.get("name");
        Configuration cfg = (Configuration) env.get("cfg");
        Template template = cfg.getTemplate("hello.ftl");
        StringWriter out = new StringWriter();
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);
        template.process(dataModel, out);
        return new Response(out.toString());
    }

    public static Response home(Map<String, Object> env) throws IOException, TemplateException {
        return render_response_from_env(env);
    }
}

class Response {
    private String content;

    public Response(String content) {
        this.content = content;
    }

    public String getContent() {
        return content;
    }
}



<!-- hello.ftl -->
<!DOCTYPE html>
<html>
<head>
    <title>Greeting</title>
</head>
<body>
    <h1>Hello, ${name}!</h1>
</body>
</html>