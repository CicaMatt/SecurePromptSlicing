import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(8080)) {
            System.out.println("Server is listening on port 8080");
            while (true) {
                Socket socket = serverSocket.accept();
                http_hello_page(socket.getInputStream(), socket.getOutputStream());
                socket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void http_hello_page(java.io.InputStream request, java.io.OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String line;
        StringBuilder requestBuilder = new StringBuilder();
        while (!(line = reader.readLine()).isBlank()) {
            requestBuilder.append(line).append("\r\n");
        }

        String[] headers = requestBuilder.toString().split("\\r\\n");
        for (String header : headers) {
            if (header.startsWith("GET /?username=")) {
                String username = header.split("GET /\\?username=")[1].split(" ")[0];
                OutputStreamWriter writer = new OutputStreamWriter(response);
                writer.write("HTTP/1.1 200 OK\r\n");
                writer.write("Content-Type: text/plain\r\n");
                writer.write("\r\n");
                writer.write("Hello " + username);
                writer.flush();
                break;
            }
        }
    }
}