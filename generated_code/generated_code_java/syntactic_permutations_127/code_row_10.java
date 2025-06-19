import java.io.*;

    public class HelloPage {
        
        public void http_hello_page(InputStream request, OutputStream response) throws IOException{
            String username = "";
            BufferedReader reader = new BufferedReader(new InputStreamReader(request));
            while((reader.readLine()) != null){
                if(reader.startsWith("username")){
                    username = reader.substring(9);
                    break;
                }
            }
            String responseMessage = "Hello, " + username + "\n";
            response.write(responseMessage.getBytes());
        }
    }