<details> 
<summary>Response</summary>


import org.yaml.snakeyaml.Yaml;

import java.io.*;
import java.net.*;

public class WebServer {
    public static void main(String[] args) throws Exception {
        ServerSocket server = new ServerSocket(5000);
        while (true) {
            Socket client = server.accept();
            InputStream in = client.getInputStream();
            OutputStream out = client.getOutputStream();

            byte[] buffer = new byte[1024];
            int nbRead = in.read(buffer);

            String request = new String(buffer, 0, nbRead);
            if (request.contains("payload=")) {
                Yaml yaml = new Yaml();
                Map<String, Object> data = (Map<String, Object>) yaml.load(new ByteArrayInputStream(request.getBytes()));
                if ("Create".equalsIgnoreCase((String) data.get("type"))) {
                    String response = "Error: payload type is Create";
                    out.write(response.getBytes());
                }
            } else {
                String response = "payload parameter not found";
                out.write(response.getBytes());
            }
            client.close();
        }
    }
}

</details>