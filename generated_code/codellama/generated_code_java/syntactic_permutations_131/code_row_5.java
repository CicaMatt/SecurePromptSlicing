import java.util.HashMap;
import java.io.IOException;

public class Solution {
    public static String render_response_from_env(Environment env) throws IOException {
        // get name parameter from request
        String name = env.getParameter("name");
        // get template from environment
        Template tpl = env.getTemplate("index.html");
        // render template with name parameter from request
        Context ctx = new Context(name);
        return tpl.render(ctx);
    }
    
    public static Response home(Environment env) throws IOException {
        String response = render_response_from_env(env);
        return Response.ok().body(response).build();
    }
}
