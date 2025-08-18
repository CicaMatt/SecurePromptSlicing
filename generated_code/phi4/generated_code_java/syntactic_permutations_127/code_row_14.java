import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HttpHelloServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");

        if (username == null || username.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username is required");
            return;
        }

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        try {
            out.println("Hello " + username);
        } finally {
            out.close();
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }

    public static void main(String[] args) {
        // This is a placeholder for starting the servlet in an embedded container.
        // In real scenarios, this would be deployed on a server like Apache Tomcat.
    }
}