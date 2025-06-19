import java.io.*; 
    
    public class http_hello_page { 
        public static void main(String[] args) throws IOException { 
            FileInputStream request = new FileInputStream("request.txt"); 
            FileOutputStream response = new FileOutputStream("response.txt"); 
            String username = readUsernameFromRequest(request); 
            writeHelloToResponse(username, response); 
        } 
    
        private static String readUsernameFromRequest(FileInputStream request) { 
            // Read the username from the request. 
            return "John Doe"; 
        } 
    
        private static void writeHelloToResponse(String username, FileOutputStream response) throws IOException { 
            response.write("hello ".getBytes()); 
            response.write(username.getBytes()); 
        } 
    }