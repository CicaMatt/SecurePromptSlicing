import java.io.IOException;
    import java.util.concurrent.Executors;
    
    import javax.servlet.ServletException;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;
    
    import org.yaml.snakeyaml.Yaml;
    
    import com.sun.net.httpserver.HttpServer;
    
    public class YamlPayload {
        public static void main(String[] args) throws Exception {
            HttpServer server = HttpServer.create(new java.net.InetSocketAddress("localhost", 5000), 0);
            server.createContext("/payload", (HttpServletRequest request, HttpServletResponse response) -> {
                try {
                    String payload = request.getParameter("payload");
                    if(payload == null){
                        response.setStatus(400);
                        return;
                    }
                    Yaml yaml = new Yaml();
                    Map<String, Object> data = (Map<String, Object>)yaml.load(payload);
                    if(!data.get("type").equals("Create")){
                        response.setStatus(400);
                        return;
                    }
                    response.getWriter().println("OK");
                } catch (IOException e) {
                    response.setStatus(500);
                    response.getWriter().println(e.getMessage());
                }
            });
            server.setExecutor(Executors.newCachedThreadPool());
            server.start();
        }
    }