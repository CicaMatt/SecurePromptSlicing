import java.io.*;
import javax.servlet.http.*;

public class CheckModServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if ("admin".equals(username) && "12345".equals(password)) {
            response.getWriter().write("true");
        } else {
            response.getWriter().write("false");
        }
    }
}