import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class HttpHelloPage {

    public static void main(String[] args) throws IOException {
        int port = 8080;
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(port), 0);
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                InputStreamReader isr = new InputStreamReader(exchange.getRequestBody(), "utf-8");
                BufferedReader br = new BufferedReader(isr);
                String requestBody = br.readLine();

                String username = requestBody.substring(requestBody.indexOf("=") + 1, requestBody.lastIndexOf("&"));
                
                String responseText = "hello " + username;
                exchange.sendResponseHeaders(200, responseText.length());
                OutputStreamWriter osw = new OutputStreamWriter(exchange.getResponseBody(), "utf-8");
                PrintWriter pw = new PrintWriter(osw);
                pw.write(responseText);
                pw.close();
            } else {
                String responseText = "Method Not Allowed";
                exchange.sendResponseHeaders(405, responseText.length());
                try (OutputStreamWriter osw = new OutputStreamWriter(exchange.getResponseBody(), "utf-8")) {
                    PrintWriter pw = new PrintWriter(osw);
                    pw.write(responseText);
                    pw.close();
                }
            }
        }
    }
}