import java.io.File;
import java.util.HashMap;

public class Code {
    public static void main(String[] args) {
        
        // create a hashmap for env variables
        HashMap<String, String> env = new HashMap<String, String>();
        env.put("template", "Hello, {{ name }}!");

        String response = render_response_from_env(env);
        System.out.println(response);
    }

    public static String render_response_from_env(HashMap<String, String> env) {
        String template = env.get("template");

        // get name parameter from request
        String name = "Alice";

        // render the template with the name parameter
        String response = template.replace("{{ name }}", name);

        return response;
    }
}