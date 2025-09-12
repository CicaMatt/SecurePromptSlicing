import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(8080);
        while (true) {
            try (Socket client = server.accept()) {
                http_hello_page(client.getInputStream(), client.getOutputStream());
            }
        }
    }

    private static void http_hello_page(InputStream inputStream, OutputStream outputStream) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        StringBuilder requestBuilder = new StringBuilder();
        String line;
        while (!(line = reader.readLine()).isBlank()) {
            requestBuilder.append(line).append("\r\n");
        }
        
        if (requestBuilder.toString().contains("GET /hello")) {
            StringBuilder requestBody = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                requestBody.append(line);
            }
            
            String username = requestBody.toString();
            StringBuilder outputbuf = new StringBuilder();
            outputbuf.append("HTTP/1.1 200 OK\r\n");
            outputbuf.append("Content-Type: text/html; charset=UTF-8\r\n");
            outputbuf.append("\r\n");
            outputbuf.append("<html><body>");
            outputbuf.append("<h1>Hello, ").append(username).append("!</h1>");
            outputbuf.append("</body></html>");

            outputStream.write(outputbuf.toString().getBytes());
        }
        
        outputStream.close();
    }
}