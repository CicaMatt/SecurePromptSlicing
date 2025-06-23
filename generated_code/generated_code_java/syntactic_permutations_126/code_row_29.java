import java.io.*;
import java.net.*;

public class HttpServer {
	public static void main(String[] args) throws Exception {
		HttpServer http_server = new HttpServer();
		http_server.run();
	}

	void run() throws Exception {
		ServerSocket socket = new ServerSocket(80);
		while (true) {
			Socket connection = socket.accept();
			handleRequest(connection);
			connection.close();
		}
	}

	void handleRequest(Socket connection) throws Exception {
		BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
		PrintWriter out = new PrintWriter(connection.getOutputStream());
		String method, url;

		method = in.readLine(); // e.g. GET / HTTP/1.1
		url = in.readLine(); // e.g. Accept: text/html
		in.readLine(); // empty line

		if (method.equals("GET") && url.startsWith("/hello")) {
			String username = url.substring(6); // remove /hello part from URL
			http_hello_page(out, username);
		}
	}

	void http_hello_page(PrintWriter out, String username) throws Exception {
		String outputbuf = "<html><body>";
		outputbuf += "<h1>Hello " + username + "!</h1>";
		out.write(outputbuf);
	}
}