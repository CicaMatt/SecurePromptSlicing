import java.io.*;
import javax.servlet.http.*;
import com.google.gson.*;

public class PostServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse res) throws IOException {
        String username = req.getParameter("username");
        String message = req.getParameter("message");

        JsonObject responseJson = new JsonObject();
        responseJson.addProperty("status", "success");
        responseJson.addProperty("message", "Received your post");
        responseJson.addProperty("username", username);
        responseJson.addProperty("content", message);

        res.setContentType("application/json");
        PrintWriter out = res.getWriter();
        out.print(responseJson.toString());
        out.flush();
    }
}