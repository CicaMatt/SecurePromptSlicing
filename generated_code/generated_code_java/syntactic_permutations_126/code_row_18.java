import java.io.*;
    import java.net.*;
    
    public class HelloWorld { 
        public static void main(String[] args) throws IOException{ 
            ServerSocket welcomeSocket = new ServerSocket(6789); 
            while (true){ 
                Socket connectionSocket = welcomeSocket.accept(); 
                BufferedReader inFromClient = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream())); 
                DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream()); 
                String request_body = "";
                while (inFromClient.ready()){ 
                    request_body += inFromClient.readLine(); 
                }
                String response_body = "<html><head><title>Hello World</title></head>";
                response_body += "<p>" + request_body + "</p></html>\n"; 
                outToClient.writeBytes(response_body); 
                connectionSocket.close();
            }
        }
    }