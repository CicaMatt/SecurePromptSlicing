java
import java.io.*;
import java.net.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class hello extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        PrintWriter outputbuf = response.getWriter();
        outputbuf.println("<html>");
        outputbuf.println("<head><title>Hello</title></head>");
        outputbuf.println("<body>");
        outputbuf.println("<h1>Greetings " + username + "</h1>");
        outputbuf.println("</body>");
        outputbuf.println("</html>");
        response.flushBuffer();
    }
}