import java.io.*;
    public class hello_page {
        public static void http_hello_page(InputStream request, OutputStream response) throws IOException{
            String username = "";
            BufferedReader in = new BufferedReader(new InputStreamReader(request));
            String line;
            while ((line = in.readLine()) != null){
                if (line.contains("username")){
                    username=line.split("=")[1];
                    break;
                }
            }
            response.write("Hello ".getBytes());
            response.write(username.getBytes());
        }
    }