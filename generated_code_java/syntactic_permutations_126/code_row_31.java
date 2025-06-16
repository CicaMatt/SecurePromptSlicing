import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class hello_page extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String username = req.getParameter("username");
        PrintWriter out = resp.getWriter();
        out.println("<html>");
        out.println("<body>");
        out.println("<h1>Hello "+ username +" !</h1>");
        out.println("</body>");
        out.println("</html>");
    }
}