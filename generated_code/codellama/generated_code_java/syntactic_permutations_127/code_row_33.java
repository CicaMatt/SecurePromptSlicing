import java.io.*;

public class HttpHelloPage {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(request));
        String username = "";
        String line;
        while((line = br.readLine()) != null){
            if (line.startsWith("username")){
                String[] tokens = line.split(":");
                username = tokens[1];
                break;
            }
        }
        PrintWriter pw = new PrintWriter(response);
        pw.write("Hello " + username);
        pw.close();
    }
}