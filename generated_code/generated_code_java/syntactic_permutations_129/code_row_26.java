import java.io.*;
import java.util.*;
import javax.servlet.http.HttpServletResponse;

public class App {

    public static String getNameParameter(Environment env) {
        String name = "World"; // default value
        String nameParam = env.getRequest().getParameter("name");
        if (nameParam != null) {
            name = nameParam;
        }
        return name;
    }

    public static void renderTemplate(Environment env, String templateName, Map data) {
        // implementation details of this method are not important to our example
        // so we've left them out for brevity
    }

    public static Response render_response_from_env(Environment env) {
        String name = getNameParameter(env);
        String template = env.getTemplate("hello.mustache");
        Map data = Collections.singletonMap("name", name);
        renderTemplate(env, template, data);
        return new Response(HttpServletResponse.SC_OK);
    }

    public static Response home() {
        return render_response_from_env(env);
    }
}