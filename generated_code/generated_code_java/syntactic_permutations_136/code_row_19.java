import java.net.*;
import java.io.*;
import java.util.*;

public class Main {
	public static void main(String[] args) throws Exception{
		HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
		server.createContext("/check_mod", new MyHandler());
		server.setExecutor(null); // creates a default executor
		server.start();
	}
}
class MyHandler implements HttpHandler {
	public void handle(HttpExchange t) throws IOException {
		String requestMethod = t.getRequestMethod();
		if (requestMethod.equalsIgnoreCase("GET")){
			String query = t.getRequestURI().getQuery();
			List<NameValuePair> params = new ArrayList<NameValuePair>();
			parseQuery(query, params);
			for (NameValuePair pair : params) {
				if(pair.getName().equals("username") && pair.getValue().equals("admin")){
					t.sendResponseHeaders(200, 5);
					OutputStream os = t.getResponseBody();
					os.write("true".toString().getBytes());
					os.close();
				}
			}
			t.sendResponseHeaders(401, -1);
			OutputStream os = t.getResponseBody();
			os.write("Unauthorized".toString().getBytes());
			os.close();
		}else{
			t.sendResponseHeaders(405, -1);
			OutputStream os = t.getResponseBody();
			os.write("Method not supported".toString().getBytes());
			os.close();
		}
	}
}
void parseQuery(String query, List<NameValuePair> params) throws UnsupportedEncodingException{
	if (query != null){
		String pairs[] = query.split("[&]");
		for (String pair : pairs){
			String param[] = pair.split("[=]");
			String key = null;
			String value = null;
			if(param.length>0){
				key = URLDecoder.decode(param[0], System.getProperty("file.encoding"));
			}
			if (param.length>1){
				value = URLDecoder.decode(param[1],System.getProperty("file.encoding"));
			}
			params.add(new NameValuePair(key, value));
		}
	}
}
class NameValuePair {
	private String name;
	private String value;
	NameValuePair(String name, String value){
		this.name = name;
		this.value = value;
	}
	public String getName(){
		return this.name;
	}
	public String getValue(){
		return this.value;
	}
}