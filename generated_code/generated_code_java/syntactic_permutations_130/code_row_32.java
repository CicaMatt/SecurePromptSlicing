import java.io.*;
import java.util.*;

public class Render {
    private static String render(String template, HashMap<String, String> params) {
        return template.replace("{{name}}", params.get("name"));
    }

    private static Response render_response_from_env(Environment env) {
        Request request = env.getRequest();
        Template template = env.getTemplate("hello");
        String rendered = Render.render(template, request.params());
        return new Response(200, "text/html", rendered);
    }

    private static Response home(Environment env) {
        return Render.render_response_from_env(env);
    }
}