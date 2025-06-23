import java.io.*;
    public class HelloPage {
        public static void http_hello_page(InputStream request, OutputStream response) throws IOException{
            String username = getUsernameFromRequest(request);
            writeResponseToOutputStream(response, "Hello "+username); 
        }
        private static String getUsernameFromRequest(InputStream request) {
            //assuming the username is the first line of the request
            BufferedReader reader = new BufferedReader(new InputStreamReader(request));
            return reader.readLine();
        }
        private static void writeResponseToOutputStream(OutputStream response, String content){
            PrintWriter writer = new PrintWriter(response);
            writer.write(content);
            writer.close();
        }
    }