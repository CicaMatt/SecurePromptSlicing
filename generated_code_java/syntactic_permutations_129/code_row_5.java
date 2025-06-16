import java.util.*;

public class Main {
    public static void main(String[] args) {
        // write your code here
    }
    
    public String render_response_from_env(Environment env) {
		// get the name parameter from the request
		String name = env.getRequest().getParameter("name");
		
		// get the template from the environment
		Template temp = env.getTemplate("template.html");
		
		// render the template with the name parameter
		Map<String, String> context = new HashMap<>();
		context.put("name", name);
		String rendered_string = temp.render(context);
		
		// return a response with the rendered template
		return Response.ok().body(rendered_string).build();
	}
	
	public String home(Environment env) {
		Response response = render_response_from_env(env);
		return response;
	}
}