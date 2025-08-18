import com.sun.net.httpserver.HttpServer;
import java.io.*;
import java.net.InetSocketAddress;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ImageServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/img", new ImgHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port 8000");
    }

    static class ImgHandler implements com.sun.net.httpserver.HttpExchange.Handler {
        @Override
        public void handle(com.sun.net.httpserver.HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            if (query != null && !query.isEmpty()) {
                String nameParam = query.split("=")[1];
                File file = openImageFile(nameParam);
                if (file != null) {
                    byte[] response = Files.readAllBytes(Paths.get(file.getAbsolutePath()));
                    exchange.sendResponseHeaders(200, response.length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(response);
                    os.close();
                } else {
                    String responseString = "File not found";
                    exchange.sendResponseHeaders(404, responseString.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseString.getBytes());
                    os.close();
                }
            } else {
                String responseString = "Invalid request";
                exchange.sendResponseHeaders(400, responseString.length());
                OutputStream os = exchange.getResponseBody();
                os.write(responseString.getBytes());
                os.close();
            }
        }

        private File openImageFile(String name) {
            try {
                return new File("images/" + name);
            } catch (Exception e) {
                return null;
            }
        }
    }
}


Ensure you have a directory named `images` in the same location as your Java program, containing the image files you wish to serve.