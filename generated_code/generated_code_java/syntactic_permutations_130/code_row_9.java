import java.util.*;

public class App{
    
	public static String render_response_from_env(Environment env){
        // get name parameter from request
        String name = env.request.get("name");
        // get template from environment
        String template = env.template;
        // render the template with the name parameter
        String rendered_template = TemplateRenderer.render(template, name);
        // return a response with the rendered template
        return ResponseBuilder.build(200, "OK", rendered_template);
    }

    public static Response home(){
        // call render_response_from_env function with env variable
        String response = render_response_from_env(env);
        // return the response from the render_response_from_env
        return response;
    }   
}