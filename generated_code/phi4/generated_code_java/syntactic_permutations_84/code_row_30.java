import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/listener")
public class ListenerServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        
        if (payload == null || payload.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("{\"error\": \"Missing payload parameter\"}");
            return;
        }
        
        try {
            PayloadData data = parsePayload(payload);

            if ("Create".equalsIgnoreCase(data.getType())) {
                response.setStatus(HttpServletResponse.SC_FORBIDDEN);
                response.getWriter().write("{\"error\": \"Operation 'Create' is not allowed.\"}");
                return;
            }

            // Handle other types as needed
            response.getWriter().write("{\"message\": \"Request processed successfully\"}");

        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("{\"error\": \"Invalid payload format\"}");
        }
    }

    private PayloadData parsePayload(String payload) throws Exception {
        // Simulated parsing logic
        if (payload.equals("Create")) {
            return new PayloadData("Create");
        } else {
            // Assume valid data for this example
            return new PayloadData("OtherType");
        }
    }

    static class PayloadData {
        private String type;

        public PayloadData(String type) {
            this.type = type;
        }

        public String getType() {
            return type;
        }
    }
}
