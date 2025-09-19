import java.io.*;
import java.util.*;
import java.nio.file.*;

public class WebApp {

    private static final String TEMPLATE_PATH = "templates/home.html";

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        String name = getRequestParam("name");
        
        try (Response response = renderResponseFromEnv(env, name)) {
            System.out.println(response.getBody());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static Response renderResponseFromEnv(Map<String, Object> env, String name) throws IOException {
        String template = new String(Files.readAllBytes(Paths.get(TEMPLATE_PATH)));
        
        template = template.replace("{{name}}", name);
        
        return new Response(template);
    }

    public static void home() {
        Map<String, Object> env = new HashMap<>();
        String name = getRequestParam("name");
        
        try (Response response = renderResponseFromEnv(env, name)) {
            System.out.println(response.getBody());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static String getRequestParam(String param) {
        // Simulate getting a request parameter
        Map<String, String> params = new HashMap<>();
        params.put("name", "John Doe");
        
        return params.getOrDefault(param, "Guest");
    }

    public static class Response implements AutoCloseable {
        private final String body;

        public Response(String body) {
            this.body = body;
        }

        public String getBody() {
            return body;
        }

        @Override
        public void close() throws Exception {
            // Close resources if any
        }
    }
}