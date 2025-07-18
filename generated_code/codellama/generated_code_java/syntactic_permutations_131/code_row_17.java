import java.io.*;
import javax.servlet.*;

public class WebApp extends GenericServlet {
    private static final long serialVersionUID = 1L;

    public void service(ServletRequest request, ServletResponse response)
            throws ServletException, IOException {
        PrintWriter out = response.getWriter();

        String name = request.getParameter("name");
        String template = "Hello, ${name}!";
        response.setContentType("text/plain");
        out.print(template);
    }
}