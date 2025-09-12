import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        server.createContext("/info", (exchange -> {
            if ("GET".equals(exchange.getRequestMethod())) {
                HttpSession session = exchange.getAttributes().get("session");
                if (session != null) {
                    String username = (String) session.getAttribute("username");
                    String email = (String) session.getAttribute("email");
                    String ssnLast4 = (String) session.getAttribute("ssnLast4");

                    String responseText = "Username: " + username +
                            "<br>Email: " + email +
                            "<br>Last 4 of SSN: " + ssnLast4;

                    exchange.sendResponseHeaders(200, responseText.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseText.getBytes());
                    os.close();
                } else {
                    String responseText = "Session not found.";
                    exchange.sendResponseHeaders(404, responseText.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseText.getBytes());
                    os.close();
                }
            } else {
                String responseText = "Method Not Allowed";
                exchange.sendResponseHeaders(405, responseText.length());
                OutputStream os = exchange.getResponseBody();
                os.write(responseText.getBytes());
                os.close();
            }
        }));

        // Simulate session creation
        HttpSession mockSession = new MockHttpSession();
        mockSession.setAttribute("username", "john_doe");
        mockSession.setAttribute("email", "john@example.com");
        mockSession.setAttribute("ssnLast4", "1234");

        server.getFilters().add(new HttpExchangeFilter() {
            @Override
            public void doFilter(HttpServer exchange, HttpServletRequest request) throws IOException {
                exchange.setAttributes("session", mockSession);
            }
        });

        server.start();
    }

    static class MockHttpSession implements HttpSession {
        private final HashMap<String, Object> attributes = new HashMap<>();

        @Override
        public long getCreationTime() { return 0; }
        @Override
        public String getId() { return "mock-session"; }
        @Override
        public long getLastAccessedTime() { return 0; }
        @Override
        public void invalidate() {}
        @Override
        public boolean isNew() { return false; }
        @Override
        public void refresh() {}

        @Override
        public void setAttribute(String name, Object value) {
            attributes.put(name, value);
        }

        @Override
        public Object getAttribute(String name) {
            return attributes.get(name);
        }

        @Override
        public Enumeration<String> getAttributeNames() { return null; }
        @Override
        public String[] getValueNames() { return new String[0]; }

        @Override
        public void removeAttribute(String name) {}

        @Override
        public void setValue(String name, Object value) {}
        @Override
        public Object getValue(String name) { return null; }
        @Override
        public void removeValue(String name) {}
    }

    static abstract class HttpExchangeFilter implements com.sun.net.httpserver.HttpHandler {
        abstract void doFilter(HttpServer exchange, HttpServletRequest request) throws IOException;
        
        @Override
        public void handle(com.sun.net.httpserver.HttpExchange httpExchange) throws IOException {
            HttpServletRequest req = (HttpServletRequest) httpExchange.getAttributes().get("request");
            if (req != null) {
                doFilter(httpExchange, req);
            }
            httpExchange.handle((h) -> {});
        }
    }
}


**Note**: The `HttpServer` class is part of the JDK and not meant for full-featured web applications. For production-grade apps, consider using frameworks like Spring Boot or Java EE with a suitable server like Tomcat or Jetty. This example simulates session handling in a very basic manner; real-world applications should use more robust solutions for session management.