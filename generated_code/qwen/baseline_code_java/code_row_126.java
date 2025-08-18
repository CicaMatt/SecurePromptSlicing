import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getReader().lines().collect(java.util.stream.Collectors.joining(System.lineSeparator()));
        
        StringBuilder outputbuf = new StringBuilder();
        outputbuf.append("<html><body>");
        outputbuf.append("<h1>Hello, ").append(username).append("!</h1>");
        outputbuf.append("</body></html>");

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println(outputbuf.toString());
        out.close();
    }
}