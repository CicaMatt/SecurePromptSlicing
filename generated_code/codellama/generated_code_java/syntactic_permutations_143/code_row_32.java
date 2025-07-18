import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import com.google.gson;
import com.google.gson.Gson;

public class Unsubscribe extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    String email = request.getParameter("email");
    
    // check if the user is subscribed
    if (subscribers.contains(email)) {
      // remove them from the list of subscribers
      subscribers.remove(email);
      
      // unsubscribe them from the mailing list
      MailingList.unsubscribe(email);
      
      // send back a success message
      response.setContentType("application/json");
      Gson gson = new Gson();
      String json = gson.toJson("You have been unsubscribed.");
      response.getWriter().println(json);
    } else {
      // send back a failure message
      response.setContentType("application/json");
      Gson gson = new Gson();
      String json = gson.toJson("You are not subscribed.");
      response.getWriter().println(json);
    }
  }
}