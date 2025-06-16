import java.io.*;

public class http_hello_page{
    public static void main(String args[]) throws IOException{
        InputStream request = new FileInputStream("request");
        OutputStream response = new FileOutputStream("response");
        String username = readUsername(request);
        writeResponse(username, response);
    }

    public static String readUsername(InputStream request) throws IOException{
        StringBuilder sb = new StringBuilder();
        int i = 0;
        while((i=request.read())!=-1){
            char c = (char)i;
            if(c=='\n')
                break;
            sb.append(c);
        }
        return sb.toString();
    }

    public static void writeResponse(String username, OutputStream response) throws IOException{
        String res = "Hello "+username+"\n";
        byte[] bytes = res.getBytes();
        response.write(bytes);
    }
}