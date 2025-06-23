import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class UserInfoServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, 
                        HttpServletResponse response) 
                            throws ServletException, IOException {
        
        // Get session object created in the previous example
        HttpSession session = request.getSession();
        
        String username = (String)session.getAttribute("username");
        String email = (String)session.getAttribute("email");
        String ssn = (String)session.getAttribute("ssn");
        
        // Set response content type
        response.setContentType("text/html");
        
        PrintWriter out = response.getWriter();
        String title = "User Information";
        String docType = "<!doctype html public \"-//w3c//dtd html 4.0 " +
                "transitional//en\">\n";
        out.println(docType + "<html>\n" + "<head><title>" + title + "</title></head>\n" +
                    "<body bgcolor=\"#f0f0f0\">\n");
        
        if (username == null || username.trim().equals("")) {
            response.sendRedirect("/login");
        } else {
            out.println("<h2>" + title + "</h2>");
            out.println("<ul>");
            out.println( "<li><b>Username: </b>"+ username );
            out.println( "<li><b>Email: </b>"+ email );
            out.println( "<li><b>SSN: </b>"+ ssn );
            out.println("</ul>");
        }
        out.println("</body></html>");
    }
}