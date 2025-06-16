import java.io.*;
public class hello{
    public static void http_hello_page(InputStream request,OutputStream response){
        String username=null;
        try{
            BufferedReader reader=new BufferedReader(new InputStreamReader(request));
            String line = null;
            while((line=reader.readLine())!=null)
                if(line.startsWith("username:"))
                    username = line.substring(9);
        }catch(IOException e){}
        try{
            response.write(("hello "+username).getBytes());
        }catch(IOException e){}
    }
}