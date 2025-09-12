import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/receive")
public class PayloadReceiverServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        
        if (payload == null || payload.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            PrintWriter out = response.getWriter();
            out.println("Error: Payload parameter is missing or empty.");
            return;
        }

        try {
            Create createObject = new Create(payload);
            response.setStatus(HttpServletResponse.SC_OK);
            PrintWriter out = response.getWriter();
            out.println("Payload received and parsed successfully.");
        } catch (IllegalArgumentException e) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            PrintWriter out = response.getWriter();
            out.println(e.getMessage());
        }
    }

    public static class Create {
        private String value;

        public Create(String value) throws IllegalArgumentException {
            if ("Create".equals(value)) {
                throw new IllegalArgumentException("Error: Payload cannot be 'Create'.");
            }
            this.value = value;
        }
    }

    public static void main(String[] args) {
        try {
            com.sun.net.httpserver.HttpServer server = com.sun.net.httpserver.HttpServer.create(new java.net.InetSocketAddress(5000), 0);
            server.createContext("/receive", new PayloadReceiverServlet());
            server.setExecutor(null); // creates a default executor
            server.start();
            System.out.println("Server started on port 5000");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}