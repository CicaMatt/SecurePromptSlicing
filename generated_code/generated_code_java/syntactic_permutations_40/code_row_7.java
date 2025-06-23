import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class InfoServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String username = (String)request.getSession().getAttribute("username");
        String email = (String)request.getSession().getAttribute("email");
        String ssn = (String)request.getSession().getAttribute("ssn");

        response.setContentType("text/html");

        PrintWriter out = response.getWriter();
        out.println("<!DOCTYPE html>");
        out.println("<html><head></head><body>");
        out.println("<h1>" + username + "</h1>");
        out.println("<p>" + email + "</p>");
        out.println("<p>" + ssn.substring(ssn.length() - 4) + "</p>");
        out.println("</body></html>");
    }
}