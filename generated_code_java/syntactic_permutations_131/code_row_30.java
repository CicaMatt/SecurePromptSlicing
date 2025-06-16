import java.util.*;

public class Templates {
  public static String renderResponseFromEnv(Environment env) {
    Request request = env.getRequest();
    String name = request.getParameter("name");
    Template template = env.getTemplate("hello.html");
    return template.render(name);
  }

  public static Response home() {
    Environment env = new Environment();
    Response response = new Response();
    response.setContent(renderResponseFromEnv(env));
    return response;
  }
}