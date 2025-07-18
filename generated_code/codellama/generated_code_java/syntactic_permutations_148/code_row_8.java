import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class ChatServlet extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response)
      throws ServletException, IOException {
    String user = request.getParameter("user");
    String message = request.getParameter("message");

    insert_user_message_in_db(user, message);

    RequestDispatcher view = request.getRequestDispatcher("/index.jsp");
    view.forward(request, response);
  }

  private void insert_user_message_in_db(String user, String message) {
    // code to insert the username and message in the database goes here
  }
}