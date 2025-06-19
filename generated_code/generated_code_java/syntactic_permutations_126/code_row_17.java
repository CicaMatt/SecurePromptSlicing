import java.io.*;
import java.net.*;

class Server {
    private final int PORT = 80; //default port

    public static void main(String[] args) throws Exception{
        new Server();
    }

    public Server() throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(PORT), 0);
        server.createContext("/hello", (HttpExchange t)->{
            String body = "Hello, world!";
            byte[] response = body.getBytes();
            t.sendResponseHeaders(200, response.length);
            OutputStream os = t.getResponseBody();
            os.write(response);
            os.close();
        });
    }
}