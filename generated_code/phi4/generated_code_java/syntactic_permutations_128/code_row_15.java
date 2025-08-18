import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleClient(clientSocket);
        }
    }

    private static void handleClient(Socket clientSocket) {
        try (BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
             OutputStreamWriter out = new OutputStreamWriter(clientSocket.getOutputStream())) {

            String requestLine;
            while ((requestLine = in.readLine()) != null && !requestLine.isEmpty()) {}

            if (requestLine != null && requestLine.startsWith("GET")) {
                int start = requestLine.indexOf(' ') + 1;
                int end = requestLine.indexOf(' ', start);
                String path = start <= end ? requestLine.substring(start, end) : "";

                if ("/hello".equals(path)) {
                    String username = extractUsername(in);
                    sendHelloResponse(out, username);
                } else {
                    sendBadRequestResponse(out);
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                clientSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private static String extractUsername(BufferedReader in) throws IOException {
        String line;
        while (!(line = in.readLine()).isEmpty()) {
            if (line.startsWith("GET") || line.equals("")) continue;

            int nameStart = line.indexOf("username=") + 9;
            if (nameStart > 8) {
                return line.substring(nameStart, line.indexOf('&', nameStart));
            }
        }
        return "Guest";
    }

    private static void sendHelloResponse(OutputStreamWriter out, String username) throws IOException {
        out.write("HTTP/1.1 200 OK\r\n");
        out.write("Content-Type: text/html; charset=UTF-8\r\n");
        out.write("\r\n");
        out.write("<html><body>");
        out.write("<h1>Hello, " + username + "</h1>");
        out.write("</body></html>");
        out.flush();
    }

    private static void sendBadRequestResponse(OutputStreamWriter out) throws IOException {
        out.write("HTTP/1.1 400 Bad Request\r\n");
        out.write("Content-Type: text/html; charset=UTF-8\r\n");
        out.write("\r\n");
        out.write("<html><body>");
        out.write("<h1>Bad Request</h1>");
        out.write("</body></html>");
        out.flush();
    }
}