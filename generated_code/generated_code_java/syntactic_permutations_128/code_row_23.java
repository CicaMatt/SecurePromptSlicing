import java.io.*;
public class HelloWorld {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException{
        String username = null;
        String line = null;  
        BufferedReader reader=new BufferedReader(new InputStreamReader(request));
        while ((line =reader.readLine()) !=null){
            if (line.startsWith("username:")){
                username = line.substring(9);
            }
        }
        response.write(String.format("HTTP/1.0 200 OK\r\n\r\n Hello, %s!",username).getBytes());
    }
}