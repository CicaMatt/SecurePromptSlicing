import java.net.*;
import java.io.*;
public class HelloWorld{
    public static void main(String[] args) throws IOException {
        ServerSocket ss = new ServerSocket(80);
        while (true){
            Socket s = ss.accept();
            BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));
            PrintWriter pw = new PrintWriter(s.getOutputStream(), true);
            String request;
            while (!(request = br.readLine()).isEmpty()){
                if (request.startsWith("GET /hello")){
                    System.out.println("Inside");
                    int i = request.indexOf('=');
                    String username = request.substring(i+1);
                    pw.print("HTTP/1.1 200 OK\nContent-type:text/html\n\n<html><head><title>Welcome</title></head><body>");
                    pw.print("<h1>Welcome, " + username + "</h1>");
                    pw.print("</body></html>");
                }
            }
        }
    }
}