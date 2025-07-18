package main;

    import java.io.*;

    public class Hello {
        public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
            String username = "";
            BufferedReader br = new BufferedReader(new InputStreamReader(request));
            while (br.ready()) {
                username += (char) br.read();
            }
            String helloUser = "Hello " + username;
            response.write(helloUser.getBytes());
        }
    }