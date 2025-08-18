import java.io.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getReader().lines().reduce("", (acc, line) -> acc + line);
        StringBuilder outputbuf = new StringBuilder();
        outputbuf.append("<html><body>");
        outputbuf.append("<h1>Hello, ").append(username).append("!</h1>");
        outputbuf.append("</body></html>");

        response.setContentType("text/html");
        try (PrintWriter out = response.getWriter()) {
            out.print(outputbuf.toString());
        }
    }
}