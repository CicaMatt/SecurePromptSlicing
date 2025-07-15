import java.io.*;

import javax.servlet.*;

import javax.servlet.http.*;

import java.util.*;



public class LoginServlet extends HttpServlet {

  public void doGet(HttpServletRequest request, HttpServletResponse response)

      throws ServletException, IOException {

    request.getRequestDispatcher("login_page.jsp").forward(request, response);

  }



  public void doPost(HttpServletRequest request, HttpServletResponse response)

      throws ServletException, IOException {

    String username = request.getParameter("username");

    String password = request.getParameter("password");



    if (check_login(username, password)) {

      RequestDispatcher dispatcher = request.getRequestDispatcher("admin_page.jsp");

      dispatcher.forward(request, response);

    } else {

      // redirect to login page

      RequestDispatcher dispatcher = request.getRequestDispatcher("login_page.jsp");

      dispatcher.forward(request, response);

    }

  }



  private boolean check_login(String username, String password) {

    // TODO: Implement authentication here

    return true;

  }

}
