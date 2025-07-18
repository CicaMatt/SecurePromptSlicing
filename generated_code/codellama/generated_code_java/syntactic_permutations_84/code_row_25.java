import java.io.*; 
import javax.servlet.http.*;
import org.yaml.snakeyaml.*;

public class App extends HttpServlet{
    public void doPost(HttpServletRequest req, HttpServletResponse res) throws IOException {
        String payload = req.getParameter("payload");
        if (payload == null){
            res.setStatus(400);
            PrintWriter out = res.getWriter();
            out.println("Bad Request: no payload parameter.");
            return;
        }
        Yaml yaml = new Yaml();
        Map<String, Object> obj = (Map<String, Object>)yaml.load(payload);
        String type = (String)obj.get("type");
        if (type == null){
            res.setStatus(400);
            PrintWriter out = res.getWriter();
            out.println("Bad Request: no 'type' field in YAML.");
            return;
        }
        if (!type.equals("Create")){
            res.setStatus(400);
            PrintWriter out = res.getWriter();
            out.println("Bad Request: unknown type '" + type + "'.");
            return;
        }
        String name = (String)obj.get("name");
        if (name == null){
            res.setStatus(400);
            PrintWriter out = res.getWriter();
            out.println("Bad Request: no 'name' field in YAML.");
            return;
        }
        String data = (String)obj.get("data");
        if (data == null){
            res.setStatus(400);
            PrintWriter out = res.getWriter();
            out.println("Bad Request: no 'data' field in YAML.");
            return;
        }
        // Save the data and set the location header to /data/<name>.
    }
}