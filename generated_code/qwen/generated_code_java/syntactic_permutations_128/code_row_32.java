import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HttpPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        out.write("[" + username + "]");
        out.close();
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}