import java.util.*;
import java.io.*;

public class Home {
    public static void main(String[] args) {
        Environment env = new Environment();
        String name = "Your name";
        String response = render_response_from_env(env);
        System.out.println(response);
    }

    public static String render_response_from_env(Environment env){
        // Get the name parameter from the user request
        String name = "Your name";
        
        // Get the template from the environment
        String template = env.get_template("hello.html");
        
        // Render the template with the name parameter from the request
        return Template.render(template, name);
    }
}