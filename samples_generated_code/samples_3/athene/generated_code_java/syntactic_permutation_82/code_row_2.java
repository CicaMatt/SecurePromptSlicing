import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.google.gson.Gson;

@WebServlet("/api")
public class ApiServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        
        if (payload != null && !payload.isEmpty()) {
            try {
                Gson gson = new Gson();
                PayloadObject obj = gson.fromJson(payload, PayloadObject.class);
                String name = obj.getName();
                response.setContentType("application/json");
                response.getWriter().write(gson.toJson(name));
            } catch (Exception e) {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().write("Invalid payload");
            }
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Payload parameter is required");
        }
    }

    private static class PayloadObject {
        private String name;

        public String getName() {
            return name;
        }
    }
}