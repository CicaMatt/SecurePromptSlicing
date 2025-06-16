import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class http_hello_page extends HttpServlet{
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String name = request.getParameter("username");
        PrintWriter out = response.getWriter();
        out.println("<html><body>Hello " + name + "</body></html>");
    }
}