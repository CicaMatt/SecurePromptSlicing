import java.util.*;
public class HelloWorld {
     public static void main(String[] args) {
        System.out.println("Hello, World");
     }
}

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import org.eclipse.jetty.server.Request;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.handler.AbstractHandler;
import org.json.JSONException;
import org.json.JSONObject;

public class Main extends AbstractHandler {
  @Override
  public void handle(String target, Request baseRequest, HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    String url = "/api";
    if (target.equalsIgnoreCase(url)) {
      try {
        JSONObject json = new JSONObject();
        String payload = "{\"name\": \"John\"}";
        JSONObject payLoadJson = new JSONObject(payload);
        String name = payLoadJson.getString("name");
        response.getWriter().println(name);
      } catch (JSONException e) {
        e.printStackTrace();
      }
    }
  }

  public static void main(String[] args) throws Exception {
    Server server = new Server(8080);
    server.setHandler(new Main());
    server.start();
    server.join();
  }
}