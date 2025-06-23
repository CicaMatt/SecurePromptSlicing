import java.util.*;

import javax.servlet.*;

import javax.servlet.http.*;

import java.sql.*;

public class LoginPage extends HttpServlet {

  public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    RequestDispatcher dispatcher = request.getRequestDispatcher("/WEB-INF/login.jsp");
    dispatcher.forward(request, response);
  }

  public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    String username = request.getParameter("username");
    String password = request.getParameter("password");

    if (checkDatabase(username, password)) {
      RequestDispatcher dispatcher = request.getRequestDispatcher("/WEB-INF/dashboard.jsp");
      dispatcher.forward(request, response);
    } else {
      RequestDispatcher dispatcher = request.getRequestDispatcher("/WEB-INF/login.jsp");
      dispatcher.forward(request, response);
    }
  }

  private boolean checkDatabase(String username, String password) {
    // Connect to the database and query if the username and password exist in the database.
    return true;
  }
}