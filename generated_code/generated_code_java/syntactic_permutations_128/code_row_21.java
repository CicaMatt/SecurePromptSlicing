import java.io.*; 
import javax.servlet.*;
public class http_hello_page implements Servlet {
    public void init(ServletConfig config) { }
    public void destroy() { }
    public void service(ServletRequest request, ServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        PrintWriter out = response.getWriter();
        out.println("hello" + username);
    }
}