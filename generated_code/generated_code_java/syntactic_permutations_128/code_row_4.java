import java.io.*;
    
    public class Hello {
        public static void http_hello_page(InputStream request, OutputStream response) throws Exception{
            BufferedReader reader = new BufferedReader(new InputStreamReader(request));
            
            String username = "";
            String line = null;
            while((line = reader.readLine()) != null){
                if(line.startsWith("username=")){
                    username = line.split("=")[1];
                    break;
                }
            }
            
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));
            writer.write("hello " + username);
            writer.flush();
        }
    
    }