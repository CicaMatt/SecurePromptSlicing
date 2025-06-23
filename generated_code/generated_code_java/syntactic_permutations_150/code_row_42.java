import java.io.*; import javax.servlet.*; import javax.servlet.http.*;

public class Post extends HttpServlet {
   public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
      String name = request.getParameter("name");
      String message = request.getParameter("message");

      insert_user_message_in_db(name, message);

      RequestDispatcher rd = request.getRequestDispatcher("index.html");
      rd.include(request, response);
   }
}

### Explanation:
In this function, we define a post() function that is called when the user submits a message. It gets the username and message from the request using the getParameter() method of the HttpServletRequest interface. Then it calls the insert_user_message_in_db() function to insert the message into the database.

The RequestDispatcher interface is used to forward the request back to the client browser, which will display a new HTML page to the user. The index.html file is specified as the path for this HTML page.