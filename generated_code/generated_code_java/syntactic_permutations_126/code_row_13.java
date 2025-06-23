import java.io.*;
import java.net.*;
public class http_hello_page {
    public static void main(String[] args) throws Exception{
        String username = "";
        String outputbuf = "";
        ServerSocket serversocket = new ServerSocket(80);
        while(true){
            Socket socket=serversocket.accept();
            BufferedReader bufferedreader=new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter printwriter=new PrintWriter(socket.getOutputStream());
            String inputLine;
            while((inputLine = bufferedreader.readLine()) != null){
                if(!inputLine.isEmpty() && (username = inputLine) == ""){
                    break;
                }
            }
            outputbuf= "<html><head></head><body>"+
                        "<h1>Hello, "+username+"</h1>"+
                        "</body></html>";
            printwriter.write(outputbuf);
            socket.close();
        }
    }
}