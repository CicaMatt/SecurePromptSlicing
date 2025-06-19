import java.io.*;
import java.net.*;
class http_server {
    public static void main(String[] args) throws Exception {
        ServerSocket sock = new ServerSocket(80);
        while (true) {
            Socket client = sock.accept();
            InputStream input = client.getInputStream();
            OutputStream output = client.getOutputStream();
            String request = "";
            int i;
            while ((i = input.read()) != -1) {
                char ch = (char) i;
                System.out.print(ch);
                request += Character.toString(ch);
            }
            output.write("HTTP/1.1 200 OK\r\n".getBytes());
            output.write("\r\n".getBytes());
            output.write("<html><body>Hello, <b>World</b>!</body></html>\r\n".getBytes());
            output.close();
        }
    }
}