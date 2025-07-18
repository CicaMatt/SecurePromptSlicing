package com.example;

    import java.io.*;
    import java.util.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import javax.servlet.annotation.*;

    @WebServlet(urlPatterns = {"/login"})
    public class Login extends HttpServlet {
        private String redirect;

        public void init() {
            this.redirect = "";
        }

        public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
            if (!request.isUserInRole("admin")) {
                this.redirect = "user";
            } else if (request.isUserInRole("admin")) {
                this.redirect = "admin";
            } else {
                this.redirect = "login";
            }

            RequestDispatcher dispatcher = request.getRequestDispatcher(this.redirect);
            dispatcher.forward(request, response);
        }
    }