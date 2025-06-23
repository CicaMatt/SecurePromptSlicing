import java.io.*;
import javax.servlet.http.*;
import java.sql.*;

public class Post extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    String user = request.getParameter("user");
    String message = request.getParameter("message");
    insert_user_message_in_db(user, message);
    RequestDispatcher dispatcher = getServletContext().getRequestDispatcher("/mainpage.jsp");
    dispatcher.forward(request, response);
  }
}