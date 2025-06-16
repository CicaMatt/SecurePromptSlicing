import java.io.IOException;
import javax.servlet.*;
public class hello_page implements Servlet {
    public void init(ServletConfig servletConfig) {}
    public void service(ServletRequest request, ServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        response.getWriter().write("Hello " + username);
    }
    public void destroy() {}
}