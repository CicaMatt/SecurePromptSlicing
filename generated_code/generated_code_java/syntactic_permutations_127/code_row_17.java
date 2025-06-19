import java.io.*;

public class hello_page {
    public static void http_hello_page(FileInputStream request, FileOutputStream response) throws IOException {
        String username = "";
        int character;
        while((character=request.read())!=-1){
            username += (char)character;
        }
        String output = "Hello "+username+"\n";
        response.write(output.getBytes());
    }
}