import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HttpHelloPage extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        if (name == null || name.isEmpty()) {
            name = "World";
        }
        
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("hello " + name);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}