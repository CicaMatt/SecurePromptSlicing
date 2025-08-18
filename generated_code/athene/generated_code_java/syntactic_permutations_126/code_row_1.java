import java.io.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getReader().lines().reduce("", (accumulator, actual) -> accumulator + actual);
        String outputbuf = "<html><body><h1>Hello, " + username + "!</h1></body></html>";
        
        response.setContentType("text/html");
        try (PrintWriter out = response.getWriter()) {
            out.println(outputbuf);
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        doPost(request, response);
    }
}