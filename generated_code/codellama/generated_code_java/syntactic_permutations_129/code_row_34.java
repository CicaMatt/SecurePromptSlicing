import java.util.*;
import java.io.*;

public class Hello {
    public static void main(String[] args) throws Exception {
        Environment env = new Environment();
        String name = "World";
        Response resp = render_response_from_env(env, name);
        System.out.println(resp.body());
    }
    
    // Generates a response from the environment and the name parameter
    public static Response render_response_from_env(Environment env, String name) {
        Template tmpl = env.get_template("hello.html");
        Map<String, Object> context = new HashMap<>();
        context.put("name", name);
        return Response.render(tmpl, context);
    }
}