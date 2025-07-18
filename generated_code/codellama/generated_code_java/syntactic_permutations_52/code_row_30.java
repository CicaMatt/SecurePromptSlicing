package com.security;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class LoginServlet extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response)
      throws IOException, ServletException {
    PrintWriter out = response.getWriter();

    String username = request.getParameter("username");
    String password = request.getParameter("password");

    if (do_login(username, password)) {
      HttpSession session = request.getSession();
      session.setAttribute("username", username);
      response.sendRedirect("secretpage.html");
    } else {
      out.println("<h1>Login page</h1>");
      out.println(
          "<form action='login' method='post'>"
              + "Username: <input type='text' name='username'><br>"
              + "Password: <input type='password' name='password'><br>"
              + "<input type='submit' value='Login'>"
              + "</form>");
    }
  }

  private boolean do_login(String username, String password) {
    return true;
  }
}