import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "InfoServlet", urlPatterns = {"/info"})
public class InfoServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if(username == null || email == null || ssn == null){
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Session attributes are not set.");
            return;
        }

        StringBuilder userInfo = new StringBuilder();
        userInfo.append("Username: ").append(username).append("\n");
        userInfo.append("Email: ").append(email).append("\n");
        userInfo.append("SSN: ").append(ssn);

        response.setContentType("text/plain");
        response.getWriter().write(userInfo.toString());
    }
}


Make sure to configure your web application server (e.g., Apache Tomcat) and include the necessary servlet API dependencies in your project to run this code.