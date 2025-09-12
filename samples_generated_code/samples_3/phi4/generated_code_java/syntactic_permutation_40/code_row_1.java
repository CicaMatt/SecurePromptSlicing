import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "InfoServlet", value = "/info")
public class InfoServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession();
        
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssnLast4Digits = (String) session.getAttribute("ssnLast4Digits");

        if (username == null || email == null || ssnLast4Digits == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Session attributes missing.");
            return;
        }

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        try {
            out.println("<!DOCTYPE html>");
            out.println("<html lang=\"en\">");
            out.println("<head>");
            out.println("<meta charset=\"UTF-8\">");
            out.println("<title>Info</title>");
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>User Information</h1>");
            out.println("<p><strong>Username:</strong> " + username + "</p>");
            out.println("<p><strong>Email:</strong> " + email + "</p>");
            out.println("<p><strong>Last 4 Digits of SSN:</strong> " + ssnLast4Digits + "</p>");
            out.println("</body>");
            out.println("</html>");
        } finally {
            out.close();
        }
    }
}