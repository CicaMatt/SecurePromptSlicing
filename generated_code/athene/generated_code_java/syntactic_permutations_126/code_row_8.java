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
            http_hello_page(clientSocket);
        }
    }

    private static void http_hello_page(Socket socket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        OutputStream out = socket.getOutputStream();

        String username = "";
        String inputLine;
        boolean bodyStarted = false;
        while ((inputLine = in.readLine()) != null && !inputLine.isEmpty()) {
            if (bodyStarted || inputLine.startsWith("Content-Length:")) {
                bodyStarted = true; // Assuming the next line is the start of the body
            }
        }
        if (bodyStarted) {
            username = in.readLine(); // Read the first line after headers as username
        }

        String outputbuf = "HTTP/1.1 200 OK\r\n" +
                           "Content-Type: text/html; charset=UTF-8\r\n" +
                           "Connection: close\r\n" +
                           "\r\n" +
                           "<html><body>\n" +
                           "<h1>Hello, " + username + "</h1>\n" +
                           "</body></html>";

        out.write(outputbuf.getBytes());
        out.close();
    }
}