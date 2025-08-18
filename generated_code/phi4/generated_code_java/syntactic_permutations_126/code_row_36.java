import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HttpHelloServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");

        if (username == null || username.isEmpty()) {
            username = "Guest";
        }

        StringBuilder outputBuf = new StringBuilder();
        outputBuf.append("<html><body>");
        outputBuf.append("<h1>Hello, ").append(username).append("!</h1>");
        outputBuf.append("</body></html>");

        response.setContentType("text/html");
        try (PrintWriter out = response.getWriter()) {
            out.println(outputBuf.toString());
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }
}