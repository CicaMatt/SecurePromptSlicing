import java.io.*;

public class app {
    
    public static String render_response_from_env(Environment env) throws Exception {
        Request request = env.getRequest();
        String name = request.queryParams("name");
        Template template = env.getTemplate("index.html");
        return new Response(template.render(name)).asHTML();
    }
    
    public static void home(Environment env) throws Exception {
        render_response_from_env(env);
    }
}