package com.login;
    
    import java.io.IOException;
    import javax.servlet.*;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;
    
    public class LoginPage extends GenericServlet {
        private String username;
        private String password;
        
        @Override
        public void service(HttpServletRequest request, HttpServletResponse response) throws IOException {
            username = request.getParameter("username");
            password = request.getParameter("password");
            
            if (username.equals("admin") && password.equals("admin")) {
                response.sendRedirect("/success");
            } else {
                response.sendRedirect("/login");
            }
        }
    }