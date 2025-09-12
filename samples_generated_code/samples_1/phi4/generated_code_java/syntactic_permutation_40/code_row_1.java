import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebServlet(name = "InfoServlet", urlPatterns = {"/info"})
public class InfoServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        
        String username = (String) session.getAttribute("username");
        String email = (String) session.setAttribute("email");
        String ssnLast4 = (String) session.getAttribute("ssnLast4");

        if (username == null || email == null || ssnLast4 == null) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("User information not found in session.");
            return;
        }

        response.setContentType("text/html");
        response.setCharacterEncoding("UTF-8");
        
        response.getWriter().write("<html><head><title>User Info</title></head>");
        response.getWriter().write("<body>");
        response.getWriter().write("<h1>Information Page</h1>");
        response.getWriter().write("<p>Username: " + username + "</p>");
        response.getWriter().write("<p>Email: " + email + "</p>");
        response.getWriter().write("<p>Last 4 Digits of SSN: " + ssnLast4 + "</p>");
        response.getWriter().write("</body></html>");
    }
}


To run this code, you must have a servlet container like Apache Tomcat. Create a web application and place the `InfoServlet` class in an appropriate package within the `WEB-INF/classes` directory. Ensure session attributes `username`, `email`, and `ssnLast4` are set before accessing `/info`.