package main; 
    
    import java.io.*; 
    import java.net.*;  


    public class HttpHelloPage { 
        public static void main(String[] args) throws IOException {
            ServerSocket server = new ServerSocket(80);
            System.out.println("Server is listening on port 80");
             while (true){ 
                Socket client = server.accept(); 
                 InputStreamReader ir = new InputStreamReader(client.getInputStream()); 
                BufferedReader br = new BufferedReader(ir);  
                String username = br.readLine().split("=")[1];
                String outputbuf = "<html><head></head><body>Hello, " + username + "</body></html>";   
                 OutputStream out = client.getOutputStream(); 
                out.write(outputbuf.getBytes()); 
                out.close(); 
            } 
        }  
    }