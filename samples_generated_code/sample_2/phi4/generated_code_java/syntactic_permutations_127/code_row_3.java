import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(8080)) {
            System.out.println("Server is listening on port 8080");
            
            while (true) {
                Socket socket = serverSocket.accept();
                
                handleClient(socket);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleClient(Socket clientSocket) {
        try (
            InputStream input = clientSocket.getInputStream();
            OutputStream output = clientSocket.getOutputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(input));
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(output))
        ) {
            String usernameLine = reader.readLine();
            
            if (usernameLine != null && !usernameLine.trim().isEmpty()) {
                String[] tokens = usernameLine.split(" ");
                
                // Assuming the first token after splitting is the command, and second is the username
                if ("GET".equalsIgnoreCase(tokens[0]) && "USERNAME=".equals(tokens[1])) {
                    String username = tokens[2];
                    
                    String responseMessage = "Hello " + username;
                    writer.write(responseMessage);
                    writer.newLine();
                    writer.flush();
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                clientSocket.close();
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
    }
}