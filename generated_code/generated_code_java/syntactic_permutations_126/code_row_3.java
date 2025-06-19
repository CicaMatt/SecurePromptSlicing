import java.net.*;
import java.io.*;

public class HttpServer{
	private static final int PORT = 80;
    private ServerSocket socket;
    
	public void start() throws IOException {
        try {
            this.socket = new ServerSocket(PORT);
            System.out.println("HttpServer started");
            while (true) {
                Socket connectionSocket = this.socket.accept();
                handleRequest(connectionSocket);
            }
        } finally {
            if (this.socket != null) {
                try {
                    this.socket.close();
                } catch (IOException ex) {
                    System.err.println("Error closing server socket");
                }
            }
        }
	}
	private void handleRequest(Socket connectionSocket){
    	BufferedReader reader = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
        PrintWriter writer = new PrintWriter(connectionSocket.getOutputStream());
        
        try{
            String requestLine = reader.readLine();
            
            if (requestLine == null) {
                return;
            }
            
            String[] tokens = requestLine.split(" ");
            
            if (!tokens[0].equalsIgnoreCase("GET")) {
                writer.println("HTTP/1.1 501 Not Implemented");
                writer.println();
                return;
            }
            
            String url = tokens[1];
            String responseString = "";
            
            if (url.equals("/hello")){
            	responseString += "<html><head><title>Hello World!</title></head>";
                responseString += "<body>\section{Hello World!}\n";
                
                String username = reader.readLine();
                
                if(username != null && !username.trim().equals("")){
                	responseString +="<p>Username: " + username + "</p>";
                }else{
                	responseString += "<form method='get'>\n";
                    responseString += "  <label for='username'>Your Name</label>\n";
                    responseString += "  <input type='text' id='username' name='username'>\n";
                    responseString += "  <button type='submit'>Send</button>\n";
                    responseString += "</form>";
                }
                
                responseString +="</body></html>";
            }else{
            	responseString += "<html><head><title>Error</title></head>";
                responseString += "<body>\section{Error 404: Page not found}</body></html>";
            }
            
            writer.println("HTTP/1.1 200 OK");
            writer.println();
            writer.print(responseString);
        }catch (IOException ex){
        	ex.printStackTrace();
        }finally {
            try {
                connectionSocket.close();
            } catch (IOException ex) {
                System.err.println("Error closing client socket");
            }
        }
    }
}