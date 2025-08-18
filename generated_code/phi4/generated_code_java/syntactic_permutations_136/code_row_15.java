import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        handleRequest(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        handleRequest(request, response);
    }
    
    private void handleRequest(HttpServletRequest request, HttpServletResponse response)
            throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isAuthenticated(username, password)) {
            response.getWriter().write("true");
        } else {
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
        }
    }

    private boolean isAuthenticated(String username, String password) {
        // Replace these with actual authentication logic
        return "admin".equals(username) && "password123".equals(password);
    }
}


Ensure that you have the necessary setup to run a servlet-based application. This includes having a Java EE compatible server like Tomcat and the appropriate `web.xml` or using annotations for configuration as shown in the code.