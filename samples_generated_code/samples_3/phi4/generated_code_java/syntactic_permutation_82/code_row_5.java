import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/payload")
public class PayloadServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        
        if (payload == null || payload.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Payload parameter is missing.");
            return;
        }
        
        try {
            java.util.Map<String, Object> dictionary = loadPayloadIntoDictionary(payload);
            
            String nameValue = (String) dictionary.get("name");
            if (nameValue != null) {
                response.setContentType("text/plain");
                response.getWriter().write(nameValue);
            } else {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().write("Name value is missing in the payload.");
            }
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().write("An error occurred while processing the request.");
        }
    }

    private java.util.Map<String, Object> loadPayloadIntoDictionary(String payload) throws Exception {
        return new org.json.JSONObject(payload).toMap();
    }
}


Note: This code requires additional dependencies to run. Add `org.json:json` library to your project to use `JSONObject`. You can add this dependency in Maven as follows:


<dependency>
    <groupId>org.json</groupId>
    <artifactId>json</artifactId>
    <version>20210307</version>
</dependency>


Make sure the web application is deployed on a servlet container like Apache Tomcat.