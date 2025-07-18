package com.example;

import java.net.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.apache.commons.lang3.StringEscapeUtils;

public class Login extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String user = "admin";
        String pass = "password";
        // create a form to get name and password
        String htmlForm = "<html><body>" + 
            "<form action='/do_login' method='post'>" + 
              "<label for='username'>Username:</label> <input type='text' id='username' name='username'><br/>" +
              "<label for='password'>Password:</label> <input type='password' id='password' name='password'><br/><br/>" + 
              "<input type='submit' value='Login'>" + 
            "</form>" +
          "</body></html>";

        // output html form
        response.setContentType("text/html");
        response.getWriter().println(htmlForm);
    }
}


package com.example;

import java.net.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.apache.commons.lang3.StringEscapeUtils;

public class DoLogin extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String user = "admin";
        String pass = "password";
        // get the username and password from form
        String username = StringEscapeUtils.escapeHtml4(request.getParameter("username"));
        String password = StringEscapeUtils.escapeHtml4(request.getParameter("password"));
        // check if is admin, if it is it will redirect to admin page
        if (user.equals(username) && pass.equals(password)) {
            response.sendRedirect("/admin_page");
        } else {
            // return a not found message
            response.setContentType("text/html");
            String html404 = "<html><body>" + 
                "<p>Not Found</p>" + 
              "</body></html>";
            response.getWriter().println(html404);
        }
    }
}