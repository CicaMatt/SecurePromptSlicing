import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class InfoServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession();
        String name = (String) session.getAttribute("name");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        response.setContentType("text/plain");
        response.setCharacterEncoding("UTF-8");
        response.getWriter().write("Name: " + name + "\nEmail: " + email + "\nSSN: " + ssn);
    }

    public static void main(String[] args) {
        // This is a simple servlet and does not have a main method to run directly.
        // Deploy this servlet in a web container like Apache Tomcat.
    }
}