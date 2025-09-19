import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        while (true) {
            Socket clientSocket = serverSocket.accept();
            http_hello_page(clientSocket.getInputStream(), clientSocket.getOutputStream());
            clientSocket.close();
        }
    }

    public static void http_hello_page(java.io.InputStream request, java.io.OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String line;
        StringBuilder requestBuilder = new StringBuilder();
        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            requestBuilder.append(line).append("\r\n");
        }

        String[] headers = requestBuilder.toString().split("\\r\\n");
        for (String header : headers) {
            if (header.startsWith("GET /?username=")) {
                String username = header.substring(16);
                String httpResponse = "HTTP/1.1 200 OK\r\n" +
                                      "Content-Type: text/plain\r\n" +
                                      "\r\n" +
                                      "Hello " + username;
                response.write(httpResponse.getBytes());
                break;
            }
        }
    }
}