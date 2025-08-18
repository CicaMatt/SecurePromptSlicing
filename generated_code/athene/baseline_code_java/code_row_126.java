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
    protected void service(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        if ("/hello".equals(req.getPathInfo())) {
            http_hello_page(req, resp);
        } else {
            super.service(req, resp);
        }
    }
}