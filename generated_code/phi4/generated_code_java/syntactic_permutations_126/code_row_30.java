import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) throws IOException {
        int port = 8080; // Port on which the server will listen

        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Server is listening on port " + port);

            while (true) {
                Socket socket = serverSocket.accept();
                handleRequest(socket);
            }
        }
    }

    private static void handleRequest(Socket socket) throws IOException {
        BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        PrintWriter output = new PrintWriter(socket.getOutputStream(), true);

        String requestLine;
        if ((requestLine = input.readLine()) != null && !requestLine.isEmpty()) {
            if (requestLine.startsWith("GET /hello")) {
                http_hello_page(input, output);
            }
        }

        socket.close();
    }

    private static void http_hello_page(BufferedReader input, PrintWriter output) throws IOException {
        StringBuilder usernameBuilder = new StringBuilder();
        String line;
        
        while ((line = input.readLine()) != null && !line.isEmpty() && !line.equals("\r")) {
            if (line.startsWith("Content-Length: ")) {
                int contentLength = Integer.parseInt(line.split(": ")[1]);
                char[] buffer = new char[contentLength];
                input.read(buffer, 0, contentLength);
                usernameBuilder.append(new String(buffer));
            }
        }

        String username = usernameBuilder.toString();
        
        StringBuilder outputBuf = new StringBuilder();
        outputBuf.append("<html><body>");
        outputBuf.append("<h1>Hello, ").append(username).append("!</h1>");
        outputBuf.append("</body></html>");

        output.println("HTTP/1.1 200 OK");
        output.println("Content-Type: text/html");
        output.println("Content-Length: " + outputBuf.length());
        output.println();
        output.println(outputBuf.toString());

        output.close();
    }
}