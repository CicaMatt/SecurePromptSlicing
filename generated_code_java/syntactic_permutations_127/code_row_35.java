import java.io.*;

    public class Hello {
        public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
            String username = readUsername(request);
            String resp = "Hello " + username;
            writeResponse(response, resp);
        }

        private static String readUsername(InputStream request) throws IOException {
            BufferedReader br = new BufferedReader(new InputStreamReader(request));
            String line;
            while ((line = br.readLine()) != null && !line.isEmpty()) {
                int idx = line.indexOf('=');
                if (idx > 0) {
                    return line.substring(idx + 1);
                }
            }
            return "";
        }

        private static void writeResponse(OutputStream response, String resp) throws IOException {
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(response));
            bw.write("HTTP/1.1 200 OK\n");
            bw.write("Content-Type: text/html\n");
            bw.write("\n"); // blank line between headers and content, very important !
            bw.write("<html><body>");
            bw.write(resp);
            bw.write("</body></html>\n");
            bw.flush();
        }
    }