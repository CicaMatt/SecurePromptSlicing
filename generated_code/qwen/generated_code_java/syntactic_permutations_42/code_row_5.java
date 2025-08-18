import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class InfoServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username != null && email != null && ssn != null) {
            response.setContentType("text/plain");
            response.getWriter().write("Username: " + username + "\nEmail: " + email + "\nSSN: " + ssn);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "User information not found in session.");
        }
    }

    public static void main(String[] args) throws Exception {
        javax.servlet.http.HttpServlet servlet = new InfoServlet();
        javax.servlet.ServletConfig config = null;
        servlet.init(config);

        javax.servlet.ServletRequest request = null;
        javax.servlet.ServletResponse response = null;

        servlet.doGet(request, response);
    }
}