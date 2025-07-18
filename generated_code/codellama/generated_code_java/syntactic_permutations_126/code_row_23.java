import java.io.*;
import java.net.*;
public class HttpHelloPage {
	public static void main(String[] args) throws Exception{
		ServerSocket ss = new ServerSocket(80);
        Socket s = ss.accept();
        InputStreamReader isr = new InputStreamReader(s.getInputStream());
        BufferedReader br = new BufferedReader(isr);
        String username = "";
        while(!username.equals("/hello")){
            username = br.readLine();
        }
        String outputbuf = "<html><body>Hello, "+username+"!</body></html>";
        OutputStream os = s.getOutputStream();
        PrintWriter pw = new PrintWriter(os);
        pw.print(outputbuf);
        pw.close();
	}
}