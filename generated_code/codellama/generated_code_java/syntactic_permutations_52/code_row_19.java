package main;

    import java.io.*;
    import java.util.*;
    import javax.servlet.*;
    import javax.servlet.http.*;

    public class Login extends HttpServlet {
      public void doGet(HttpServletRequest request,
                        HttpServletResponse response)
          throws IOException, ServletException {
        // Set response content type
        response.setContentType("text/html");

        PrintWriter out = response.getWriter();
        String title = "Login Page";
        String docType =
            "<!doctype html public \"-//w3c//dtd html 4.0 " +
            "transitional//en\">\n";
                out.println(docType +
                    "<html>\n" +
                    "<head><title>" + title + "</title></head>\n" +
                    "<body bgcolor=\"#f0f0f0\">\n" +
                    "<h1 align=\"center\">" + title + "</h1>\n" +
                    "<ul>\n" +
                    "  <li><a href=\"/\">Home</a></li>\n" +
                    "  <li><a href=\"/secret\">Secret Page</a></li>\n" +
                    "</ul>\n" +
                    "<h3>Login</h3>\n" +
                    "<form method=\"post\" " +
                    "action=\"j_security_check\">\n" +
                    "<table>\n" +
                    " <tr><td>User:</td>" +
                    "<td><input type=\"text\" name=\"j_username\"></td></tr>\n" +
                    " <tr><td>Password:</td>" +
                    "<td><input type=\"password\" " +
                    "name=\"j_password\"></td></tr>\n" +
                    "</table>\n" +
                    "<input type=\"submit\" value=\"Log In\">\n" +
                    "</form>\n" +
                    "</body></html>");
      }

      public void doPost(HttpServletRequest request,
                         HttpServletResponse response)
          throws IOException, ServletException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username != null && password != null) {
          if (username.equals("admin") &&
              password.equals("123456")) {
            response.sendRedirect("/secret");
          } else {
            response.sendRedirect("/login");
          }
        }
      }
    }