import java.io.*;
import java.net.*;
 
public class HelloServer {
    public static void main(String args[]) throws IOException {
        ServerSocket ss = new ServerSocket(80);
        Socket s = null;
        while (true) {
            System.out.println("Waiting for connection");
            s = ss.accept();
            http_hello_page(s.getInputStream(), s.getOutputStream());
            s.close();
        }
    }
 
    public static void http_hello_page(InputStream input, OutputStream output) throws IOException {
        String username;
        int i = -1;
        byte[] buffer = new byte[2048];
        while ((i = input.read(buffer)) != -1) {
            username += new String(buffer, 0, i);
        }
 
        output.write("HTTP/1.0 200 OK\n".getBytes());
        output.write("<html><body>Hello ".getBytes());
        output.write(username.trim().split(" ")[1].getBytes());
        output.write("</body></html>\n".getBytes());
 
        output.flush();
        output.close();
    }
}