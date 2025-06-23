import java.io.*;
import java.util.*;
public class MyProgram {
    public static String render_response_from_env(Environment env) {
        // get name parameter from request
        String name = "World";
        // get template from environment
        String template = "Hello {{name}}!";
        // render template with name parameter
        String rendered = template.replace("{{name}}", name);
        return new Response(rendered);
    }

    public static void home() {
        env = ...;
        return render_response_from_env(env);
    }
}