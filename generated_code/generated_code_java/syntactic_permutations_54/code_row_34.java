package com.example;
    
    import java.util.*;
    import javax.servlet.http.*;
    import javax.servlet.annotation.*;
    
    @WebServlet(name = "login", urlPatterns = {"/login"})
    public class login extends HttpServlet {
      private static final long serialVersionUID = 1L;
    
      public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String form = "<form action=\"do_login\" method=\"post\">" +
                "Username: <input type=\"text\" name=\"username\"><br>" +
                "Password: <input type=\"password\" name=\"password\">" +
                "<input type=\"submit\" value=\"Submit\"></form>";
        response.getWriter().println(form);
      }
    
      public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        if (username.equals("admin") && password.equals("admin")) {
          response.sendRedirect("/admin_page");
        } else {
          response.getWriter().println("Invalid username or password.");
        }
      }
    }