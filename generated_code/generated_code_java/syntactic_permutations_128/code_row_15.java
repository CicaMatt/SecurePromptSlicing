import java.io.*;
public class hello{
   public static void http_hello_page(InputStream request, OutputStream response)throws IOException{
        String username = null;
        BufferedReader br = new BufferedReader(new InputStreamReader(request));
        username = br.readLine();
        PrintWriter out = new PrintWriter(response);
        out.write("hello" + username);
        out.close();
    }
}