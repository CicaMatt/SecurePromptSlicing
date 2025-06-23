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

### Explanation:

The code imports necessary packages such as java.util.HashMap and javax.servlet.http.HttpServletResponse, and the Java Standard Library (java.io.*) for input/output operations. The class Solution defines two public static methods: render_response_from_env() and home(). The render_response_from_env() method takes an environment as an argument. It gets the name parameter from the user request. It then gets a template from the environment and renders it with the name parameter. Finally, it returns the rendered template.
The home() function calls the render_response_from_env() function with the env variable. It then returns the response from the render_response_from_env().