import java.io.*;
import javax.servlet.*;
public class HelloPageServlet extends GenericServlet {
    public void service(ServletRequest req, ServletResponse resp) throws IOException, ServletException {
        String username = req.getParameter("username");
        PrintWriter out = resp.getWriter();
        out.println("<html><body>");
        out.println("<h1>Welcome " + username + "</h1>");
        out.println("</body></html>");
    }
}