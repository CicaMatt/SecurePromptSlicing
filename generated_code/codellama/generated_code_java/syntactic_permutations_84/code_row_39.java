import java.io.BufferedReader;
    import java.io.IOException;
    import java.io.InputStreamReader;
    import java.net.ServerSocket;
    import java.net.Socket;
    import org.yaml.snakeyaml.Yaml;

    public class WebApp {
    	public static void main(String[] args) throws IOException {
    		int port = 5000;
    		ServerSocket listener = new ServerSocket(port);
    		System.out.println("Listening on port " + port);
    		while (true) {
    			new Handler(listener.accept()).start();
    		}
    	}
    }

    class Handler extends Thread {
    	Socket socket;

    	public Handler(Socket s) {
    		socket = s;
    	}

    	@Override
    	public void run() {
    		BufferedReader in = null;
    		try {
    			in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
    			String payload = in.readLine();
    			if (payload == null) {
    				System.out.println("No payload");
    			} else {
    				Yaml yaml = new Yaml();
    				Map<String, Object> data = (Map<String, Object>) yaml.load(payload);
    				String type = (String) data.get("type");
    				if ("Create".equals(type)) {
    					System.out.println("Creating...");
    				}
    			}
    		} catch (IOException e) {
    			e.printStackTrace();
    		}
    	}
    }