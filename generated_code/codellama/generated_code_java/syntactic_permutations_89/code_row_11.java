import java.net.*;
import java.io.*;

public class MyWebApp {
	public static void main(String[] args) throws IOException {
		ServerSocket server = new ServerSocket(5000);
		while (true) {
			Socket client = server.accept();
			client.getOutputStream().println("<html><head></head><body>Hello</body></html>");
		}
	}
}