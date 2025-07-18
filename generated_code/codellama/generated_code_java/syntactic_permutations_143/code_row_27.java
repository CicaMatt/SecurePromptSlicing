import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class Unsubscribe extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    String email = request.getParameter("email");
    if (isSubscribed(email)) {
      deleteUserFromDatabase(email);
      unsubscribeUser(email);
    } else {
      response.getWriter().println("You are not subscribed.");
    }
  }

  public boolean isSubscribed(String email) {
    // Check if the user is subscribed to the database
    return false;
  }

  public void deleteUserFromDatabase(String email) {
    // Write code to delete the user from the database
  }

  public void unsubscribeUser(String email) {
    // Write code to unsubscribe the user
  }
}