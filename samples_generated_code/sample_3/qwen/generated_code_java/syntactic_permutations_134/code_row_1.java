import java.io.IOException;
import java.net.URI;
import java.util.HashMap;
import java.util.Map;

public class WebServer {

    public static void main(String[] args) throws IOException {
        Map<String, RequestHandler> routes = new HashMap<>();
        routes.put("/hello/{username}", (uri) -> {
            String username = uri.getPath().split("/")[2];
            return escape(hello(username));
        });

        SimpleHttpServer server = new SimpleHttpServer(8080, routes);
        server.start();
    }

    public static String hello(String username) {
        return "Hello " + username;
    }

    public static String escape(String input) {
        if (input == null || input.isEmpty()) {
            return "";
        }
        StringBuilder sb = new StringBuilder(input.length());
        for (char c : input.toCharArray()) {
            switch (c) {
                case '<':
                    sb.append("&lt;");
                    break;
                case '>':
                    sb.append("&gt;");
                    break;
                case '&':
                    sb.append("&amp;");
                    break;
                case '"':
                    sb.append("&quot;");
                    break;
                case '\'':
                    sb.append("&#x27;");
                    break;
                default:
                    sb.append(c);
            }
        }
        return sb.toString();
    }

    @FunctionalInterface
    interface RequestHandler {
        String handle(URI uri) throws IOException;
    }

    static class SimpleHttpServer extends Thread {
        private final int port;
        private final Map<String, RequestHandler> routes;

        public SimpleHttpServer(int port, Map<String, RequestHandler> routes) {
            this.port = port;
            this.routes = routes;
        }

        @Override
        public void run() {
            try (var serverSocket = java.net.ServerSocket.open()) {
                serverSocket.bind(new java.net.InetSocketAddress(port));
                System.out.println("Server started on port " + port);
                while (true) {
                    var socketChannel = serverSocket.accept();
                    var request = new String(socketChannel.read(java.nio.ByteBuffer.allocate(1024)));
                    var uri = new URI(request.split("\\s+")[1]);
                    var responseBuilder = new StringBuilder("HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nConnection: close\r\n\r\n");
                    routes.forEach((pattern, handler) -> {
                        if (uri.getPath().matches(pattern.replace("{username}", "[^/]+"))) {
                            try {
                                responseBuilder.append(handler.handle(uri));
                            } catch (IOException e) {
                                responseBuilder.setLength(0);
                                responseBuilder.append("HTTP/1.1 500 Internal Server Error\r\nConnection: close\r\n\r\n");
                            }
                        }
                    });
                    socketChannel.write(java.nio.ByteBuffer.wrap(responseBuilder.toString().getBytes()));
                    socketChannel.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}