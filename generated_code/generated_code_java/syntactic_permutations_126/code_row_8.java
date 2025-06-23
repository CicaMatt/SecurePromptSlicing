import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class hello_page extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)throws ServletException, IOException  {
        String username = request.getParameter("username");
        OutputStream outputbuf = response.getOutputStream();
        outputbuf.println("<html>");
        outputbuf.println("<body bgcolor=white>");
        outputbuf.println("<h1>Hello " + username + "</h1>");
        outputbuf.println("</body>");
        outputbuf.println("</html>");
        response.close();
    }
}