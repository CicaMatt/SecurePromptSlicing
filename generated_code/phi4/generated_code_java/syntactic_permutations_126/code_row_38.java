import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello")
public class HelloServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");

        if (username == null || username.trim().isEmpty()) {
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

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }
}