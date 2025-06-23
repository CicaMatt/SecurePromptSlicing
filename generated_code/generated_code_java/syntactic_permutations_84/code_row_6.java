import java.io.*; import java.net.*; 
import org.yaml.snakeyaml.Yaml;

class Server { public static void main(String[] args) { try { ServerSocket serverSocket = new ServerSocket(5000); Socket socket = serverSocket.accept(); InputStream inputStream = socket.getInputStream(); OutputStream outputStream = socket.getOutputStream(); BufferedReader in = new BufferedReader(new InputStreamReader(inputStream)); String payload=in.readLine(); if (!payload.contains("payload=")) { out.println("Payload parameter is missing"); return; } Yaml yaml = new Yaml(); Map<String, Object> data = (Map<String, Object>) yaml.load(payload); if (data.get("type") != "Create") { out.println("Type parameter should be Create"); return; }
	} catch (Exception e) { System.err.println(e); } } }