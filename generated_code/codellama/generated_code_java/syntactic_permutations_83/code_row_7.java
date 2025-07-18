import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
public class ServletExample extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {
        String name = request.getParameter("name");
        if (name != null) {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println(name);
        }
    }
}