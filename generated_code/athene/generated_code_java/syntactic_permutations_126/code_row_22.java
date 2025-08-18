import java.io.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
    protected void http_hello_page(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        StringBuilder outputbuf = new StringBuilder();
        outputbuf.append("<html><body>");
        outputbuf.append("<h1>Hello, ").append(username).append("!</h1>");
        outputbuf.append("</body></html>");

        response.setContentType("text/html;charset=UTF-8");
        try (PrintWriter out = response.getWriter()) {
            out.print(outputbuf.toString());
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        http_hello_page(request, response);
    }
}