import java.io.*;
import java.net.*;

public class HelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(12345);
        Socket clientSocket = serverSocket.accept();
        
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);

        String username = in.readLine();
        out.println("hello " + username);

        in.close();
        out.close();
        clientSocket.close();
        serverSocket.close();
    }
}