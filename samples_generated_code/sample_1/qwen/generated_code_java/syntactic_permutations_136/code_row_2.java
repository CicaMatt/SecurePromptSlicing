import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class CheckModServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password123".equals(password)) {
            response.setContentType("text/plain");
            PrintWriter out = response.getWriter();
            out.println("true");
        }
    }

    public static void main(String[] args) {
        // This main method is just for completeness. In a real-world scenario, this servlet would be deployed in a web server like Tomcat.
    }
}