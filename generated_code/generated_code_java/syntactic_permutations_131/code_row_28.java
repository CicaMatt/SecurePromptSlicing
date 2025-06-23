import java.util.*;
import java.io.*;

public class App {
  
    public static String render_response_from_env(Environment env) {
        Map<String, Object> context = new HashMap<>();
        context.put("name", "Anna");
        Template template = env.getTemplate("home.html");
        return template.render(context);
    }
  
    public static void main(String[] args) {
        Environment env = new Environment();
        String rendered = render_response_from_env(env);
        System.out.println(rendered);
    }
}