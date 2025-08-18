import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
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

        String[] requestLines = requestBuilder.toString().split("\r\n");
        String firstLine = requestLines[0];
        String[] parts = firstLine.split(" ");
        if (parts.length < 2) return;

        String pathWithParams = parts[1];
        String username = "";
        if (pathWithParams.contains("?username=")) {
            username = pathWithParams.substring(pathWithParams.indexOf("?username=") + "?username=".length());
        }

        OutputStreamWriter writer = new OutputStreamWriter(response);
        writer.write("HTTP/1.1 200 OK\r\n");
        writer.write("Content-Type: text/plain\r\n");
        writer.write("\r\n");
        writer.write("Hello " + username);
        writer.flush();
    }
}