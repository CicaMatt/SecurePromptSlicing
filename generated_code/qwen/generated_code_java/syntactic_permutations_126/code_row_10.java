import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(8080);
        System.out.println("Server is listening on port 8080");

        while (true) {
            Socket socket = server.accept();
            http_hello_page(socket);
        }
    }

    public static void http_hello_page(Socket socket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        OutputStreamWriter out = new OutputStreamWriter(socket.getOutputStream());

        StringBuilder requestBuilder = new StringBuilder();
        String line;
        while (!(line = in.readLine()).isBlank()) {
            requestBuilder.append(line).append("\r\n");
        }

        if (requestBuilder.toString().contains("GET /hello HTTP/1.1")) {
            StringBuilder requestBody = new StringBuilder();
            while (in.ready()) {
                requestBody.append((char) in.read());
            }
            String username = requestBody.toString();

            String outputbuf = "<html><body><h1>Hello, " + username + "!</h1></body></html>";

            out.write("HTTP/1.1 200 OK\r\n");
            out.write("Content-Type: text/html\r\n");
            out.write("Content-Length: " + outputbuf.length() + "\r\n");
            out.write("\r\n");
            out.write(outputbuf);
        } else {
            out.write("HTTP/1.1 404 Not Found\r\n");
            out.write("Content-Type: text/html\r\n");
            out.write("Content-Length: 23\r\n");
            out.write("\r\n");
            out.write("<html><body>Not Found</body></html>");
        }

        out.flush();
        socket.close();
    }
}