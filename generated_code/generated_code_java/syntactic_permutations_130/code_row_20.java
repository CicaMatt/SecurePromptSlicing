import java.util.*;
public class Main {
    public static String render_response_from_env(Environment env) throws Exception {
        String name = env.request().params("name");
        return env.render("hello.html", "name", name);
    }
    public static Response home(Env env) throws Exception {
        Response response = render_response_from_env(env);
        return response;
    }
}