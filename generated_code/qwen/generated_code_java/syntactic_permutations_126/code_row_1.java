import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getReader().lines().collect(Collectors.joining(System.lineSeparator()));
        String outputbuf = "<html><body><h1>Hello, " + username + "!</h1></body></html>";

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.print(outputbuf);
        out.close();
    }
}