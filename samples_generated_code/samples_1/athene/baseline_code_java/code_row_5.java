import java.util.HashMap;
import java.util.Map;

interface Router {
    void bind(String url, Handler handler);
}

interface Handler {
    String handle(Request request);
}

class Request {
    private Map<String, String> params = new HashMap<>();

    public void addParam(String key, String value) {
        params.put(key, value);
    }

    public String getParam(String key) {
        return params.get(key);
    }
}

class TemplateRenderer {
    private Map<String, String> templates = new HashMap<>();

    public TemplateRenderer addTemplate(String name, String content) {
        templates.put(name, content);
        return this;
    }

    public String render(String name, Map<String, String> context) {
        String template = templates.get(name);
        for (Map.Entry<String, String> entry : context.entrySet()) {
            template = template.replace("{{" + entry.getKey() + "}}", entry.getValue());
        }
        return template;
    }
}

class HelloHandler implements Handler {
    private TemplateRenderer renderer;

    public HelloHandler(TemplateRenderer renderer) {
        this.renderer = renderer;
    }

    @Override
    public String handle(Request request) {
        String username = request.getParam("username");
        Map<String, String> context = new HashMap<>();
        context.put("username", username);
        return renderer.render("hello.html", context);
    }
}

public class WebApp {
    private Router router;
    private TemplateRenderer templateRenderer;

    public WebApp(Router router) {
        this.router = router;
        this.templateRenderer = new TemplateRenderer();
        setupRoutes();
    }

    private void setupRoutes() {
        router.bind("/hello/<username>", new HelloHandler(templateRenderer));
    }

    public static void main(String[] args) {
        Router router = new Router() {
            @Override
            public void bind(String url, Handler handler) {
                System.out.println("Binding URL: " + url);
                // Simulate a request to /hello/John
                Request request = new Request();
                String username = url.substring("/hello/".length());
                request.addParam("username", username);
                System.out.println(handler.handle(request));
            }
        };

        templateRenderer.addTemplate("hello.html", "Hello, {{username}}!");

        new WebApp(router);
    }
}