package main;
    
    import javax.servlet.http.*;
    import java.io.*;
    import java.util.*;
    import javax.servlet.*;
    import javax.servlet.annotation.WebServlet;
    
    @WebServlet(name = "Login", urlPatterns = {"/login"})
    public class Login extends HttpServlet {
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            
            if (isValidUser(username, password)) {
                System.out.println("Successfully logged in!");
                RequestDispatcher rd = request.getRequestDispatcher("/dashboard");
                rd.forward(request, response);
            } else {
                System.out.println("Invalid login credentials.");
                RequestDispatcher rd = request.getRequestDispatcher("/login");
                rd.include(request, response);
            }
        }
        
        private boolean isValidUser(String username, String password) {
            // Code here to check the database and return true or false based on that check.
            return true;
        }
    }