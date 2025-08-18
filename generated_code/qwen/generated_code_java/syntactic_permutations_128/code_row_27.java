import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(8080);
        while (true) {
            Socket client = server.accept();
            handleRequest(client);
        }
    }

    private static void handleRequest(Socket client) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
        OutputStreamWriter out = new OutputStreamWriter(client.getOutputStream());

        StringBuilder requestBuilder = new StringBuilder();
        String line;
        while ((line = in.readLine()) != null && !line.isEmpty()) {
            requestBuilder.append(line).append("\r\n");
        }

        String request = requestBuilder.toString();
        String username = getUsernameFromRequest(request);

        String response = "HTTP/1.1 200 OK\r\n" +
                          "Content-Type: text/html\r\n" +
                          "Connection: close\r\n" +
                          "\r\n" +
                          "<html><body><h1>Hello " + username + "</h1></body></html>";
        out.write(response);
        out.flush();
        client.close();
    }

    private static String getUsernameFromRequest(String request) {
        String[] lines = request.split("\r\n");
        for (String line : lines) {
            if (line.startsWith("username=")) {
                return line.substring(9);
            }
        }
        return "Guest";
    }
}