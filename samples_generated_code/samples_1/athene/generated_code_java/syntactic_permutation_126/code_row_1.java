import java.io.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getReader().lines().reduce("", (accumulator, actual) -> accumulator + actual);
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Hello, " + username + "!</h1>");
        out.println("</body></html>");
        out.close();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        doPost(request, response);
    }
}