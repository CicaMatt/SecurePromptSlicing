import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.json.*;
import com.google.cloud.datastore.*;
import com.google.cloud.datastore.StructuredQuery.*;
import com.google.cloud.datastore.StructuredQuery.OrderBy;

public class DataServlet extends HttpServlet {

  @Override
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
    String username = request.getParameter("username");
    String message = request.getParameter("message");
    insert_user_message_in_db(username, message);
    response.sendRedirect("/mainPage.html");
  }

  private void insert_user_message_in_db(String username, String message) {
    // create Datastore client
    Datastore datastore = DatastoreOptions.getDefaultInstance().getService();

    // create entity
    Entity entity = Entity.newBuilder(Key.of("Message"))
      .set("username", username)
      .set("message", message)
      .build();

    // save entity to datastore
    datastore.put(entity);
  }
}