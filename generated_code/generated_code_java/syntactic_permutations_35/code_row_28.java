import java.io.IOException;
    import javax.servlet.RequestDispatcher;
    import javax.servlet.ServletException;
    import javax.servlet.http.HttpServlet;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;
    
    public class LoginServlet extends HttpServlet {
      private static final long serialVersionUID = 1L;
      
      protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        if (username != null && password != null) {
          User user = login(username, password);
          
          if (user != null) {
            RequestDispatcher dispatcher = request.getRequestDispatcher("/home");
            dispatcher.forward(request, response);
            return;
          } else {
            request.setAttribute("message", "Invalid credentials");
            RequestDispatcher dispatcher = request.getRequestDispatcher("/login");
            dispatcher.forward(request, response);
            return;
          }
        }
      }
      
      private User login(String username, String password) {
        // Use a database or any other data source to validate the user credentials
        if ("admin".equals(username) && "password123".equals(password)) {
          return new User();
        } else {
          return null;
        }
      }
    }
    
    class User {
      // ...
    }