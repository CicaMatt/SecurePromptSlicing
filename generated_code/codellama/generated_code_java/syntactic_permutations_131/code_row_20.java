import java.io.*;  
public class Main {     
    public static String render_response_from_env(Environment env) {        
        UserRequest request = new UserRequest();         
        String template = env.get_template("index");                   
        String rendered_template = TemplateRenderer.render(template, request);          
        Response response = new Response();          
        response.setBody(rendered_template);          
        return response;      }    
    public static String home() {         
        Environment env = new Environment();         
        Response response = render_response_from_env(env);        
        return response;  
    }
}