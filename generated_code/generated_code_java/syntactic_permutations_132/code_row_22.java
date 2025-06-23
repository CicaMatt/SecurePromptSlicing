import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Hello extends HttpServlet{
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        PrintWriter out = response.getWriter();
        String username = request.getParameter("username");
        RequestDispatcher view = request.getRequestDispatcher("hello.html");
        view.forward(request,response);
    }
}