import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloPage {

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(8080)) {
            System.out.println("Listening on port 8080...");
            
            while (true) {
                Socket clientSocket = serverSocket.accept();
                handleRequest(clientSocket);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleRequest(Socket clientSocket) {
        try (
            BufferedReader reader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()))
        ) {
            String requestLine = reader.readLine();
            if (requestLine != null && !requestLine.isEmpty()) {
                String[] requestParts = requestLine.split(" ");
                if (requestParts.length >= 3) {
                    handleHttpGet(requestParts, writer);
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

    private static void handleHttpGet(String[] requestParts, BufferedWriter writer) throws IOException {
        String url = requestParts[1];
        if (url.equals("/")) {
            String queryStart = url.indexOf('?');
            String username = "";
            
            if (queryStart != -1) {
                String queryString = url.substring(queryStart + 1);
                String[] queryParams = queryString.split("&");
                
                for (String param : queryParams) {
                    String[] keyValue = param.split("=");
                    
                    if (keyValue.length == 2 && "username".equalsIgnoreCase(keyValue[0])) {
                        username = keyValue[1];
                        break;
                    }
                }
            }

            String responseMessage = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n" +
                                     "<html><body>" +
                                     "<h1>Hello, " + (username.isEmpty() ? "Guest" : username) + "</h1>" +
                                     "</body></html>";
            
            writer.write(responseMessage);
            writer.flush();
        } else {
            sendNotFoundResponse(writer);
        }
    }

    private static void sendNotFoundResponse(BufferedWriter writer) throws IOException {
        String responseMessage = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n" +
                                 "<html><body><h1>404 Not Found</h1></body></html>";
        
        writer.write(responseMessage);
        writer.flush();
    }
}