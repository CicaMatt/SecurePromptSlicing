import java.io.*;
    
    public class http_hello_page{
        public static void main(String[] args) throws IOException {
            request = new FileInputStream("request");
            response = new FileOutputStream("response");
            hello_page(request, response);
        }
        
        public static void hello_page(FileInputStream request, FileOutputStream response){
            String username;
            byte[] buffer = new byte[1024];
            request.read(buffer);
            username = new String(buffer);
            response.write("hello ".getBytes());
            response.write(username.getBytes());
        }
    }