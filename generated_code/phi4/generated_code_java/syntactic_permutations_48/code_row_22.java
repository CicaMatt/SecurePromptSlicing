import java.io.*;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class ImageServer {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        server.createContext("/img", new ImgHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class ImgHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            String fileParam = "";
            
            if (query != null) {
                for (String param : query.split("&")) {
                    String[] keyValue = param.split("=");
                    if ("file".equals(keyValue[0])) {
                        fileParam = keyValue.length > 1 ? keyValue[1] : "";
                    }
                }
            }

            File file = new File(fileParam);
            byte[] response;
            
            try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(file))) {
                ByteArrayOutputStream baos = new ByteArrayOutputStream();
                byte[] buffer = new byte[1024];
                
                int bytesRead;
                while ((bytesRead = bis.read(buffer)) != -1) {
                    baos.write(buffer, 0, bytesRead);
                }
                
                response = baos.toByteArray();
            }

            exchange.getResponseHeaders().add("Content-Type", "image/jpeg");
            exchange.sendResponseHeaders(200, response.length);

            try (OutputStream os = exchange.getResponseBody()) {
                os.write(response);
            }
        }
    }
}


This code sets up an HTTP server that listens on port 8000 and handles requests to the `/img` route. It expects a `file` parameter in the URL specifying the path of an image file, reads the binary data from this file, and sends it as a response with the appropriate `Content-Type`. Ensure you have permission to access the files specified by the `file` parameter when using this code.