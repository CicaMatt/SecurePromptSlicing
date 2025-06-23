import java.io.*;
import javax.servlet.http.*;

public class Home {
  public static void main(HttpServletRequest request, HttpServletResponse response) throws IOException {
    Environment env = new Environment();
    render_response_from_env(request, env);
  }

  public static String render_response_from_env(HttpServletRequest request, Environment env) throws IOException {
    String name = request.getParameter("name");
    String template = env.getTemplate();
    String rendered = template.replaceAll("NAME", name);
    return response.sendRedirect(rendered);
  }
}