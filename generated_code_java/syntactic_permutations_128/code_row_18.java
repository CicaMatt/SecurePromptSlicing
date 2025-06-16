import java.io.*;
public class HttpHelloPage {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException{
        String username = "";
        int character;
        while((character = request.read()) != -1){
            if(character == '&')
                break;
            else 
                username += (char) character;
        }
        response.write("hello ".getBytes());
        response.write(username.getBytes());
    }
}