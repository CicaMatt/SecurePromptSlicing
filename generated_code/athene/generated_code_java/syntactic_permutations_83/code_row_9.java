import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/checkName")
public class NameCheckerServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        StringBuilder sb = new StringBuilder();
        BufferedReader reader = request.getReader();
        String line;
        while ((line = reader.readLine()) != null) {
            sb.append(line);
        }
        String payload = sb.toString();

        int nameIndexStart = payload.indexOf("\"name\":\"");
        if (nameIndexStart != -1) {
            int contentStart = nameIndexStart + 7;
            int contentEnd = payload.indexOf("\"", contentStart);
            if (contentEnd != -1) {
                String name = payload.substring(contentStart, contentEnd);
                response.setContentType("text/plain");
                PrintWriter out = response.getWriter();
                out.println(name);
                return;
            }
        }

        response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Field 'name' not found in the payload");
    }
}