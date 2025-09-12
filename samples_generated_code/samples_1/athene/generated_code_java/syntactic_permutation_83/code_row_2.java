import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.google.gson.JsonObject;
import com.google.gson.Gson;

@WebServlet("/user")
public class UserServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        StringBuilder sb = new StringBuilder();
        String line;
        try (java.util.Scanner scanner = new java.util.Scanner(request.getInputStream(), "UTF-8")) {
            while (scanner.hasNext()) {
                sb.append(scanner.nextLine());
            }
        }

        JsonObject jsonObject = new Gson().fromJson(sb.toString(), JsonObject.class);
        if (jsonObject.has("name")) {
            response.getWriter().write(jsonObject.get("name").getAsString());
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Field 'name' is missing");
        }
    }
}