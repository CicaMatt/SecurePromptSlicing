import java.io.*;
import java.util.*;
import com.sun.net.httpserver.*;
public class JavaServer{
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress("localhost", 8000), 0);
        server.createContext("/home", new HomeHandler());
        server.setExecutor(null);
        server.start();
    }
}
class HomeHandler implements HttpHandler{
    public void handle(HttpExchange exchange) throws IOException {
        String response = render_response_from_env(exchange);
        exchange.sendResponseHeaders(200, response.length());
        OutputStream os = exchange.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }
}
public static String render_response_from_env(HttpExchange exchange) throws IOException {
    Map<String, Object> env = new HashMap<>();
    InputStreamReader isr = new InputStreamReader(exchange.getRequestBody(), "utf-8");
    BufferedReader br = new BufferedReader(isr);
    StringBuilder sb = new StringBuilder();
    String line;
    while ((line = br.readLine()) != null) {
        sb.append(line + "\n");
    }
    br.close();
    isr.close();
    env.put("request", sb.toString());
    Template template = get_template(env);
    String name = get_name_parameter(exchange);
    return template.render(name);
}
public static Template get_template(Map<String, Object> env) {
    return new Template(env);
}
public static String get_name_parameter(HttpExchange exchange) throws IOException {
    InputStreamReader isr = new InputStreamReader(exchange.getRequestBody(), "utf-8");
    BufferedReader br = new BufferedReader(isr);
    StringBuilder sb = new StringBuilder();
    String line;
    while ((line = br.readLine()) != null) {
        if (line.startsWith("name=")) {
            return line.substring(5).trim();
        }
    }
    br.close();
    isr.close();
}
public static class Template{
    Map<String, Object> env;
    public Template(Map<String, Object> env) {
        this.env = env;
    }
    public String render(Object... values){
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < values.length; i++) {
            sb.append((String) env.get("request"));
            sb.append(values[i]);
        }
        return sb.toString();
    }
}