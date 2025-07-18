package codeguru;
    
    import java.io.*;
    import java.util.*;
    import java.net.URLEncoder;
    import javax.servlet.*;
    import javax.servlet.http.*;
    
    public class LoginServlet extends HttpServlet {
      private static final long serialVersionUID = 1L;
      
      protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        try{
          if (isValidUser(username, password)) {
            response.sendRedirect("/success.jsp");
          } else {
            response.sendRedirect("/cant_login.jsp?error=true&username=" + URLEncoder.encode(username,"UTF-8"));
          }
        } catch (Exception e) {
          response.sendRedirect("/internal_server_error.jsp");
        }
      }
      
      private boolean isValidUser(String username, String password){
        // connect to database and check if the user with given username and password exists
        return false; 
      }
    }