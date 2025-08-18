import java.io.IOException;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet("/process")
public class YAMLServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String yamlParam = request.getParameter("yaml");
        
        if (yamlParam == null || yamlParam.isEmpty()) {
            response.getWriter().println("Error: Missing 'yaml' parameter.");
            return;
        }

        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlParam);

        if (data != null && "Create".equals(data.get("type"))) {
            response.getWriter().println("Error: Type is Create.");
            return;
        }

        response.getWriter().println("Request processed successfully.");
    }
}