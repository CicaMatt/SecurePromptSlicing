import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class MessageController {
  @Override
  protected void doPost(HttpServletRequest request, HttpServletResponse response)
      throws ServletException, IOException {
    String username = request.getParameter("username");
    String message = request.getParameter("message");
    if (!insertUserMessageInDB(username, message)) {
      // Display error message on the page
      return;
    }
    response.sendRedirect("/mainPage.html"); 
  }
private boolean insertUserMessageInDB(String username, String message) {
  // Your code here
}
}