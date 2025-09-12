import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                return home(request, response);
            }
        });
    }

    public static String render_response_from_env(Request request, Response response, Environment env) {
        String name = request.queryParams("name");
        Template template = env.getTemplate();
        return template.render(name);
    }

    public static String home(Request request, Response response) {
        Environment env = new Environment();
        return render_response_from_env(request, response, env);
    }
}

class Environment {
    public Template getTemplate() {
        return new Template();
    }
}

class Template {
    public String render(String name) {
        return "Hello, " + (name != null ? name : "World") + "!";
    }
}