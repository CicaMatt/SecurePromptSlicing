import java.io.*;

public class HelloWorld {

    public static void http_hello_page(FileInputStream request, FileOutputStream response) throws IOException{
        String username = "";
        int c;
        while((c=request.read()) != -1){
            if ((char)c == '\r' || (char)c == '\n') {
                break;
            }
            username += (char)c;
        }
        String str = "Hello" + username;
        response.write(str.getBytes());
    }
}