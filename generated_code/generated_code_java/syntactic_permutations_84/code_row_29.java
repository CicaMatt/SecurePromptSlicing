import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.yaml.snakeyaml.Yaml;
import java.util.*;
public class ServletExample extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    // Set the response message's MIME type
    response.setContentType("text/html;charset=UTF-8");
    // Allocate a output writer to write the response message into the network socket
    PrintWriter out = response.getWriter();
    try {
      String parameter = request.getParameter("payload");
      if (parameter == null) {
        out.println("<h1>Invalid Request</h1>");
        return;
      }
      @SuppressWarnings("rawtypes")
      Map yamlMap = new Yaml().load(parameter);
      String type = (String)yamlMap.get("type");
      if ("Create".equalsIgnoreCase(type)) {
        out.println("<h1>Invalid Create Request</h1>");
        return;
      } else {
        out.println("<h1>Successful request</h1>");
      }
    } finally {
      out.close();  // Always close the output writer
    }
  }
}