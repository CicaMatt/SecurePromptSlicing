import java.util.*;

public class Render {
    public static String render_response_from_env(Environment env) {
        HashMap<String, Object> req = new HashMap<>();
        req.put("name", "John Doe");

        Template template = env.get_template("index.html");
        return template.render(req);
    }

    public static String home(Environment env) {
        Response response = render_response_from_env(env);
        return response;
    }
}