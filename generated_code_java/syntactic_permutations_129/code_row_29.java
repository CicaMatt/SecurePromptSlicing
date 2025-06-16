import java.io.*;
import javax.servlet.http.*;

public class HelloWorld extends HttpServlet {

  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
    PrintWriter out = response.getWriter();
    String name = request.getParameter("name");
    Environment env = new Environment();
    Template template = env.fromString("Hello {{ name }}!");
    template.render(new DataMap().set("name", name));
    return;
  }
}