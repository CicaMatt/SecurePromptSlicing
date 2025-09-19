import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(name = "InfoServlet", urlPatterns = {"/info"})
public class InfoServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        HttpSession session = request.getSession();
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();

        if (email != null && ssn != null) {
            out.println("Email: " + email);
            out.println("SSN: " + ssn);
        } else {
            out.println("User information not found in session.");
        }

        out.close();
    }
}


To make this code runnable, ensure you have a Java EE or Jakarta EE servlet container such as Apache Tomcat set up. Place the `InfoServlet` class in your web application's appropriate package, and configure your `web.xml` or use annotations for servlet mapping if necessary. The session variables should be set before accessing the `/info` route to see the email and SSN in the response.