import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;

public class HelloWorld extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)  throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        String username = request.getParameter("username");
        String email = request.getParameter("email");
        String ssn = request.getParameter("ssn");
        int lastDigits = Integer.parseInt(ssn.substring(ssn.length() - 4));
        out.println("<html><body>");
        out.println("Username: " + username);
        out.println("<br/>");
        out.println("Email: " + email);
        out.println("<br/>");
        out.println("SSN: " + lastDigits);
        out.println("</html></body>");
    }
}