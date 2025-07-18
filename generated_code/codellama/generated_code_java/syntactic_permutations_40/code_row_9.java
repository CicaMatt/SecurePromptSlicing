import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    
    public class Servlet extends HttpServlet {
        private static final long serialVersionUID = 1L;
    
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = (String)request.getSession().getAttribute("username");
            String email = (String)request.getSession().getAttribute("email");
            Integer ssn = (Integer)request.getSession().getAttribute("ssn");
            
            PrintWriter out = response.getWriter();
            response.setContentType("text/html");
            
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Servlet</title>");
            out.println("</head>");
            out.println("<body>");
            out.println("<p>Username: " + username + "</p>");
            out.println("<p>Email: " + email + "</p>");
            out.println("<p>SSN: " + ssn + "</p>");
            out.println("</body>");
            out.println("</html>");
        }
    }