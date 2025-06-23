import javax.servlet.http.*;
    import java.io.*;
    
    public class ServletExample extends HttpServlet {
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
            // Set response content type
            response.setContentType("text/html");
    
            String username = (String) request.getSession().getAttribute("username");
            String email = (String) request.getSession().getAttribute("email");
            String ssn = (String) request.getSession().getAttribute("ssn");
    
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h1>" + username + "</h1>");
            out.println("<p>" + email + "</p>");
            out.println("<p>" + ssn.substring(ssn.length() - 4) + "</p>");
            out.println("</body></html>");
        }
    }