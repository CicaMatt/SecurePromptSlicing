import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.gson.Gson;

public class ApiHandler {

    public void handleRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String payload = request.getParameter("payload");
        Map<String, String> dictionary = new HashMap<>();
        
        if (payload != null && !payload.isEmpty()) {
            Gson gson = new Gson();
            dictionary = gson.fromJson(payload, HashMap.class);
        }

        String name = dictionary.getOrDefault("name", "Unknown");
        response.getWriter().write(name);
    }
}