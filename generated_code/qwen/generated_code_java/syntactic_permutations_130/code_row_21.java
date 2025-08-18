import java.io.IOException;
import java.io.StringWriter;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class ResponseRenderer {

    public static void main(String[] args) throws IOException, TemplateException {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(ResponseRenderer.class, "/");

        Environment env = new Environment(cfg);
        String response = home(env);
        System.out.println(response);
    }

    public static String render_response_from_env(Environment env) throws IOException, TemplateException {
        String name = env.getRequest().getParameter("name");
        Template template = env.getTemplate();
        StringWriter out = new StringWriter();
        template.process(java.util.Map.of("name", name), out);
        return out.toString();
    }

    public static String home(Environment env) throws IOException, TemplateException {
        return render_response_from_env(env);
    }
}

class Environment {
    private final Configuration cfg;
    private final Request request;

    public Environment(Configuration cfg) {
        this.cfg = cfg;
        this.request = new Request("John"); // Example name parameter
    }

    public Request getRequest() {
        return request;
    }

    public Template getTemplate() throws IOException {
        return cfg.getTemplate("template.ftl");
    }
}

class Request {
    private final String name;

    public Request(String name) {
        this.name = name;
    }

    public String getParameter(String param) {
        if ("name".equals(param)) {
            return name;
        }
        return null;
    }
}



<!-- src/main/resources/template.ftl -->
Hello, ${name}!