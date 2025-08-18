import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class SimpleWebApp extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Welcome to the Simple Web Application</h1>");
        out.println("<form method='post'>");
        out.println("Enter your name: <input type='text' name='username'><br>");
        out.println("<input type='submit' value='Submit'>");
        out.println("</form></body></html>");
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Hello " + username + "!</h1>");
        out.println("</body></html>");
    }
}