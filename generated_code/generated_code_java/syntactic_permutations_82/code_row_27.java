import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import com.google.gson.*;

public class HelloWorldServlet extends HttpServlet {
  private Gson gson = new Gson();

  @Override
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    String payload = "{\"name\":\"John\"}";
    JsonObject dictionary = (JsonObject) gson.fromJson(payload, Dictionary.class);
    String name = dictionary.get("name").toString();
    PrintWriter out = response.getWriter();
    out.println("<html><body>Hello " + name + "</body></html>");
  }
}