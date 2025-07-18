import java.io.*; 
import java.util.*; 
  
public class Main {
    public static String render_response_from_env(Environment env) {
        Request request = env.getRequest();
        Template template = env.getTemplate();
        String rendered_template = template.render(request);
        return new Response(rendered_template);
    }

    public static String home(Environment env) {
        render_response_from_env(env);
    }
}