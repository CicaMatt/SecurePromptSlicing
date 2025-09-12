import java.io.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
    protected void http_hello_page(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getReader().lines().reduce("", (accumulator, actual) -> accumulator + actual);
        StringBuilder outputbuf = new StringBuilder();
        outputbuf.append("<html><body>");
        outputbuf.append("<h1>Hello, ").append(username).append("!</h1>");
        outputbuf.append("</body></html>");

        response.setContentType("text/html");
        try (PrintWriter out = response.getWriter()) {
            out.print(outputbuf.toString());
        }
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        http_hello_page(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        http_hello_page(req, resp);
    }
}