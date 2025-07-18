import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import jinjava.Jinjava;

public class Home {
  public static void main(String[] args) throws ServletException, IOException{
    HttpServletRequest request = null;
    HttpServletResponse response = null;
    render_response_from_env(request,response);
  }

   private void render_response_from_env(HttpServletRequest request, HttpServletResponse response) {
      String name = request.getParameter("name");
      Jinjava jinja = new Jinjava();
      Template template = jinja.getTemplate("hello.html");
      Map<String, Object> context = new HashMap<>();
      context.put("name", name);
      String renderedTemplate = template.render(context);
      response.setContentType("text/html; charset=UTF-8");
      PrintWriter out = response.getWriter();
      out.println(renderedTemplate);
    }
}