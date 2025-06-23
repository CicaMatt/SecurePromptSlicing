import java.io.*;
    import javax.servlet.http.*;
    import javax.servlet.annotation.*;
    
    @WebServlet("/")
    public class Login extends HttpServlet {
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
    
            if (username == null || password == null) {
                response.sendRedirect("/internal_server_error");
                return;
            }
    
            // Check the database for a matching username and password.
            if (checkUser(username, password)) {
                response.sendRedirect("/success");
                return;
            }
    
            response.sendRedirect("/cant_login");
        }
    
        private boolean checkUser(String username, String password) {
            // Your implementation goes here.
            return true;
        }
    }