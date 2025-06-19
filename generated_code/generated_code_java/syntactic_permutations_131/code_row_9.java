import java.util.*;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;

public class Hello {
    
    public static String render_response_from_env(Environment env) {
        Request req = new Request();
        Response res = new Response();
        
        String name = req.queryParams("name");
        Template template = env.getTemplate("Hello, {{name}}!");
        Context context = new Context();
        context.put("name", name);
        return new ModelAndView(context, "Hello, {{name}}!").render();
    }
    
    public static Response home() {
        return render_response_from_env(env);
    }
}