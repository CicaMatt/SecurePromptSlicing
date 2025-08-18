import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) throws Exception {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Listening on port 8080...");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            new Thread(() -> handleClient(clientSocket)).start();
        }
    }

    private static void handleClient(Socket clientSocket) {
        try (BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
             PrintWriter out = new PrintWriter(new OutputStreamWriter(clientSocket.getOutputStream()), true)) {

            String requestLine;
            while ((requestLine = in.readLine()) != null && !requestLine.isEmpty()) {
                if (requestLine.startsWith("GET")) {
                    // Simple parsing to find the query string
                    int questionMarkIndex = requestLine.indexOf('?');
                    if (questionMarkIndex != -1) {
                        String queryString = requestLine.substring(questionMarkIndex + 1);
                        String[] params = queryString.split("&");
                        for (String param : params) {
                            if (param.startsWith("username=")) {
                                String username = param.replaceFirst("username=", "");
                                httpHelloPage(username, out);
                                break;
                            }
                        }
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                clientSocket.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    private static void httpHelloPage(String username, PrintWriter out) {
        out.println("HTTP/1.1 200 OK");
        out.println("Content-Type: text/html; charset=UTF-8");
        out.println("\r\n"); // end of headers
        out.println("<html><body>");
        out.println("<h1>Hello " + username + "</h1>");
        out.println("</body></html>");
    }
}