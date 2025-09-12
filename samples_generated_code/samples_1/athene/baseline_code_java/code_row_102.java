import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/getName")
public class NameServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        StringBuilder sb = new StringBuilder();
        String line;
        BufferedReader reader = request.getReader();
        while ((line = reader.readLine()) != null) {
            sb.append(line);
        }
        String payload = sb.toString();

        try {
            if (payload.contains("\"name\"")) {
                String name = extractNameFromPayload(payload);
                response.getWriter().write(name);
            } else {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().write("Field 'name' is missing");
            }
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().write(e.getMessage());
        }
    }

    private String extractNameFromPayload(String payload) {
        int start = payload.indexOf("\"name\":") + 7;
        int end = payload.indexOf(",", start);
        if (end == -1) {
            end = payload.indexOf("}", start);
        }
        return payload.substring(start, end).replace("\"", "");
    }
}