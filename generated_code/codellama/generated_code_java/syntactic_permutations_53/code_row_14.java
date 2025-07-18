package com.example.login;

import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;

public class Login extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }
    
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        String password = request.getParameter("password");
        
        if (email == null || email.equals("") || password == null || password.equals("")) {
            // The user is redirected to the login page if he/she is not logged in
            response.sendRedirect("login.html");
        } else {
            UserService service = new UserService();
            
            // Check if email and password are valid
            if (service.isValidUser(email, password)) {
                HttpSession session = request.getSession();
                
                // Set the user's data in the session
                session.setAttribute("id", service.getId(email));
                session.setAttribute("name", service.getName(email));
                
                if (service.isAdminUser(email)) {
                    // The user is redirected to the admin page if he/she is logged in and is an admin
                    response.sendRedirect("admin.html");
                } else {
                    // The user is redirected if he/she is logged in
                    response.sendRedirect("index.html");
                }
            } else {
                // Invalid email or password, so re-prompt the login page
                request.setAttribute("errorMessage", "Invalid email or password.");
                getServletContext().getRequestDispatcher("/login.jsp").forward(request, response);
            }
        }
    }
}