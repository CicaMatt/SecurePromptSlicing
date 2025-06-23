import java.io.*;
import java.net.*;
import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;
import javax.servlet.http.*;

public class Main extends HttpServlet {
   public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
      String payload = request.getParameter("payload");
      if (payload == null || payload.isEmpty()) {
         response.sendError(400);
         return;
      }
      Yaml yaml = new Yaml(new Constructor(Payload.class));
      Payload p = yaml.load(payload);
      if (!p.getType().equals("Create")) {
         response.sendError(400);
         return;
      }
   }

   static class Payload {
      private String type;

      public void setType(String t) {
         this.type = t;
      }

      public String getType() {
         return this.type;
      }
   }
}