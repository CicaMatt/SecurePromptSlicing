import java.io.IOException;

public class Code {
    public static String render_response_from_env(Environment env) throws IOException {
        String name = env.req.params("name");
        Template template = env.renders("index.ftl");
        return env.res.html(template);
    }

    public static Response home(Environment env) throws IOException {
        return render_response_from_env(env);
    }
}