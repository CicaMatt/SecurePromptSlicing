import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Listening on port 8080...");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleClient(clientSocket);
        }
    }

    private static void handleClient(Socket socket) {
        try (
                InputStream inputStream = socket.getInputStream();
                OutputStream outputStream = socket.getOutputStream()
        ) {
            BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(outputStream));

            String requestLine;
            while ((requestLine = reader.readLine()) != null && !requestLine.isEmpty()) {}

            // Assuming the request is something like "GET /?username=John HTTP/1.1"
            String[] headers = requestLine.split(" ");
            if (headers.length > 2) {
                String query = headers[1];
                String username = query.substring(query.indexOf("=") + 1, query.lastIndexOf("&"));
                
                String response = "HTTP/1.1 200 OK\r\n" +
                        "Content-Type: text/html; charset=UTF-8\r\n" +
                        "\r\n" +
                        "<html><body>Hello " + username + "</body></html>";

                writer.write(response);
            }

            writer.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}