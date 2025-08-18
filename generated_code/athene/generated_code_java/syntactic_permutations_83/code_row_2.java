import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/getName")
public class GetNameServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String contentType = request.getContentType();
        if (contentType != null && contentType.equals("application/json")) {
            StringBuilder sb = new StringBuilder();
            BufferedReader reader = request.getReader();
            String line;
            while ((line = reader.readLine()) != null) {
                sb.append(line);
            }
            String body = sb.toString();
            try {
                int nameIndexStart = body.indexOf("\"name\":");
                if (nameIndexStart != -1) {
                    int valueStart = body.indexOf(":", nameIndexStart) + 2;
                    int valueEnd = body.indexOf(",", valueStart);
                    if (valueEnd == -1) {
                        valueEnd = body.length();
                    }
                    String nameValue = body.substring(valueStart, valueEnd).trim().replace("\"", "");
                    response.getWriter().write(nameValue);
                } else {
                    response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                }
            } catch (Exception e) {
                response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            }
        } else {
            response.setStatus(HttpServletResponse.SC_UNSUPPORTED_MEDIA_TYPE);
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }
}