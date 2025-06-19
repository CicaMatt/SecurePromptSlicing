import java.io.*; 
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class HelloWorldServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        RequestDispatcher dispatcher = getServletContext().getRequestDispatcher("/WEB-INF/hello.jsp");
        if (dispatcher != null) {
            dispatcher.forward(request, response);
        }
    }
}