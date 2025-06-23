import java.util.*;
import jinjava.*;

public class RenderResponseFromEnv {
    public static String renderResponseFromEnv(Environment env, HttpRequest request) {
        Map<String, Object> context = new HashMap<>();
        context.put("name", request.getParameter("name"));
        Template template = env.getTemplate("hello.html");
        String renderedTemplate = env.render(template, context);
        return Response.ok(renderedTemplate).build();
    }

    public static void home(Environment env) {
        HttpRequest request = RequestFactory.create();
        String response = renderResponseFromEnv(env, request);
        System.out.println(response);
    }
}