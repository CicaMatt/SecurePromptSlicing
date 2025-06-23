import java.io.PrintStream;
import javax.servlet.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
public class Servlet{
    public void service(ServletRequest request, ServletResponse response){
        PrintStream out = new PrintStream(response.getOutputStream());
        HttpServletRequest httpReq = (HttpServletRequest)request;
        String name = httpReq.getParameter("name");
        Template template = (Template)request.getAttribute("template");
        response.setContentType("text/html");
        out.println(template.render_response_from_env((Environment)request, name));
    }
}