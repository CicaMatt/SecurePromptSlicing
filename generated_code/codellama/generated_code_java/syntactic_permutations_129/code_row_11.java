import java.util.Map;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;

public class Hello {

    public static String render_response_from_env(String name, Map<String, Object> env){
        // get the template from the environment
        String template = env.get("name");
        // render the template with the name parameter
        return new ModelAndView(null, "name"), engine);
    }

    public static String home(Map<String, Object> env) {
        // call the render_response_from_env function
        String response = render_response_from_env("name", env);
        return response;
    }
}