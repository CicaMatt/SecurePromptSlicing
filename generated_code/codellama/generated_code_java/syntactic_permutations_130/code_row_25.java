import java.util.*;

public class Main {
    public static String render_response_from_env(Environment env) {
        String name = env.request.name;
        Template template = env.get_template("index");
        return template.render(name=name);
    }

    public static Response home() {
        return render_response_from_env(env);
    }
}