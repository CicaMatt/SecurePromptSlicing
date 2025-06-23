import java.io.*;
import java.util.*;
public class Hello {
    public static void main(String[] args) throws Exception{
        HashMap<String, Object> env = new HashMap<>();
        render_response_from_env(env);
    }
    
    private static void render_response_from_env(HashMap<String, Object> env) {
        // get name parameter from the user request
        String name = (String) env.get("name");
        
        // get template from the environment
        String template = (String) env.get("template");
        
        // render template with the name parameter
        System.out.println(template.replaceAll("\\{\\{ name \\}\\}", name));
    }
}