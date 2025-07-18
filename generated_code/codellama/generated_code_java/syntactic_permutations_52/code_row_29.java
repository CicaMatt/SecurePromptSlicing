import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    
    public class SecretPage extends HttpServlet {
      private static final long serialVersionUID = 1L;
      
      protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        String username = (String) request.getSession().getAttribute("username");
        if (username == null) {
          response.sendRedirect("/login");
        } else {
          out.println("<html>");
          out.println("<head><title>" + "Secret settings" + "</title></head>");
          out.println("<body bgcolor=\"#fdf5e6\">");
          out.println("Welcome, " + username);
          out.println("</body>");
          out.println("</html>");
        }
      }
    }