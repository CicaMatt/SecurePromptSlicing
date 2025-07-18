package main;
import com.sun.net.httpserver.*;
import java.util.regex.Pattern;
public class HelloWorld {
	public static void main(String[] args) throws Exception{
		HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
		server.createContext("/", new RedirectHandler());
		server.setExecutor(null); // creates a default executor
		server.start();
	}
	static class RedirectHandler implements HttpHandler {
		public void handle(HttpExchange t) throws Exception{
			String target = t.getRequestURI().getPath();
			if (target.matches(".*example\\.com.*")){
				t.getResponseHeaders().add("Location", target);
			} else {
				t.getResponseHeaders().add("Location", "/");
			}
			t.sendResponseHeaders(302, -1);
			t.close();
		}
	}
}