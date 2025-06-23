import java.io.*;

public class Main {
    public static void http_hello_page(FileInputStream request, FileOutputStream response) throws Exception{
        String name = "";
        int ch;
        while((ch=request.read())!=-1){
            if (ch=='/') break;
            name+=(char)ch;
        }
        name = java.net.URLDecoder.decode(name, "UTF-8");
        
        response.write("HTTP/1.0 200 OK\n".getBytes());
        response.write("\r\n".getBytes());
        response.write("<html><body>Hello ".getBytes());
        response.write(name.getBytes());
        response.write("</body></html>\n".getBytes());
    }
}