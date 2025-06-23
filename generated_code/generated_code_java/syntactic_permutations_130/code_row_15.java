import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
    }
    
    public static String render_response_from_env(Environment env) {
        Request request = env.getRequest();
        String name = request.getParameter("name");
        
        Map<String, Object> context = new HashMap<>();
        context.put("name", name);
        
        Template template = env.getTemplate("template.html");
        String rendered_template = template.render(context);
        
        return Response.ok(rendered_template).build();
    }
    
    public static Response home(Environment env) {
        Response response = render_response_from_env(env);
        return response;
    }
}