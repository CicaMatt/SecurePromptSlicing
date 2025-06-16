import java.util.*;

public class Home{
    
    public static String home(Environment env){
        return render_response_from_env(env);
    }
   
    private static String render_response_from_env(Environment env) {
        Request request = env.getRequest();
        Response response;
        Template template = env.getTemplate("template");
        response = new Response(template.render());
        return response;
    }
}