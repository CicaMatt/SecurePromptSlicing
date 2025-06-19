import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class Env extends GenericServlet {
    public void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String template = "index.html";
        String rendered_template = render_response_from_env(request);
        response.getWriter().println(rendered_template);
    }
    public String render_response_from_env(HttpServletRequest request) throws ServletException, IOException {
        return "index.html";
    }
}