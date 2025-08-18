import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HttpHelloPageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getReader().lines().collect(Collectors.joining());
        String outputbuf = "<html><body><h1>Hello, " + username + "</h1></body></html>";

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.write(outputbuf);
        out.close();
    }
}