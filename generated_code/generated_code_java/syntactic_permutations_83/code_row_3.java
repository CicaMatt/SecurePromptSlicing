import java.util.HashMap;
import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class HelloWorld extends HttpServlet {
  protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
    
    HashMap<String, String> data = new HashMap<>();
    data.put("name", "World");
    response.getWriter().print(data);
  }
}