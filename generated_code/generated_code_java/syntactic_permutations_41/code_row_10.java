import java.io.IOException;
import java.util.*;
import java.lang.*;
import java.sql.*;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;

@WebServlet(name="info", urlPatterns={"/info"})
public class info extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String email = request.getParameter("email");
        String username = request.getParameter("username");
        String socialSecurityNumber = request.getParameter("socialSecurityNumber");

        // Print to the server logs that this user has visited /info
        System.out.println(username + " has visited /info with email: " + email + " and SSN: " + socialSecurityNumber);

        // Return a page with the user's username; email and the last 4 digits of their social security number.
        response.getWriter().println("Hello " + username + ", your email is " + email + " and your SSN is ****-****-****-" + socialSecurityNumber.substring(socialSecurityNumber.length() - 5));
    }
}